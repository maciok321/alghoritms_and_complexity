#include "Game.h"
#include <iostream>
#include <string>
#include "MoveGenerator.h"
#include <algorithm>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include <optional>

Game::Game() : currentPlayer(PieceColor::White), humanPlayer(PieceColor::White), aiPlayer(PieceColor::Black), ai(aiPlayer, 4) {}

bool Game::parseMove(const std::string& from, const std::string& to, Move& move)
{
    if (from.length() != 2 || to.length() != 2)
    {
        std::cerr << "Invalid move format. Use format like 'e2 e4'." << std::endl;
        return false; // Invalid format
    }
    if (from[0] < 'a' || from[0] > 'h' || from[1] < '1' || from[1] > '8' ||
        to[0] < 'a' || to[0] > 'h' || to[1] < '1' || to[1] > '8')
    {
        std::cerr << "Invalid move format. Columns must be a-h and rows must be 1-8." << std::endl;
        return false; // Invalid format
    }
    // Convert the from and to strings (e.g., "e2", "e4") to board coordinates
    int fromCol = from[0] - 'a';
    int fromRow = from[1] - '1'; // Convert '1'-'8' to 0-7
    int toCol = to[0] - 'a';
    int toRow = to[1] - '1'; // Convert '1'-'8' to 0-7

    // Validate the move
    if (board.isInsideBoard(fromRow, fromCol) && board.isInsideBoard(toRow, toCol))
    {
        move = Move(fromRow, fromCol, toRow, toCol);
        return true;
    }
    return false;
}

std::string Game::moveToString(const Move& move)
{
    char fromCol = 'a' + move.fromCol;
    char fromRow = '1' + move.fromRow;
    char toCol = 'a' + move.toCol;
    char toRow = '1' + move.toRow;

    return std::string() + fromCol + fromRow + " " + toCol + toRow;
}

void Game::switchPlayer()
{
    currentPlayer = (currentPlayer == PieceColor::White) ? PieceColor::Black : PieceColor::White;
}

bool Game::isMoveLegal(const Move& move)
{
    std::vector<Move> legalMoves = MoveGenerator::generateMoves(board, currentPlayer);
    return std::find(legalMoves.begin(), legalMoves.end(), move) != legalMoves.end();
}

void Game::runCommandLineInterface()
{
    board.printBoard();

    std::string input;

    while (true)
    {
        if (currentPlayer == aiPlayer)
        {   
            auto start = std::chrono::high_resolution_clock::now();
            Move bestMove = ai.findBestMove(board);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            board.makeMove(bestMove);
            std::cout << "Nodes visited: " << ai.getNodesVisited() << " AI plays: " << moveToString(bestMove) << " Time taken: " << duration.count() << " ms" << std::endl;
            board.printBoard();
            switchPlayer();
            continue;
        }

        else{
                std::cout << "Enter your move (e.g., 'e2 e4') or 'exit' to quit: ";
            
            std::getline(std::cin, input);

            if (input == "exit")
            {
                std::cout << "Exiting game." << std::endl;
                break;
            }

            std::istringstream iss(input);
            std::string from, to;

            if (!(iss >> from >> to))
            {
                std::cerr << "Invalid input. Use format like 'e2 e4'." << std::endl;
                continue;
            }

            Move move(0, 0, 0, 0);

            if (!parseMove(from, to, move))
            {
                continue;
            }

            if (isMoveLegal(move))
            {
                board.makeMove(move);
                board.printBoard();
                switchPlayer();
            }
            else
            {
                std::cerr << "Illegal move. Try again." << std::endl;
            }
        }
    }
}

void Game::runGraphicalInterface()
{
    Renderer renderer;
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Chess Minimax");

    int selectedRow = -1;
    int selectedCol = -1;
    bool pieceSelected = false;

    while (window.isOpen())
    {
        // 1. Jeśli teraz ruch AI, wykonaj go poza obsługą eventów
        if (currentPlayer == aiPlayer)
        {
            // zmierz czas, jeśli chcesz
            // Move aiMove = ai.findBestMove(board);
            // board.makeMove(aiMove);
            // switchPlayer();
            // pieceSelected = false;
            std::vector<Move> aiMoves = MoveGenerator::generateMoves(board, aiPlayer);
            if (aiMoves.empty())
            {
                if (MoveGenerator::isKingInCheck(board, aiPlayer))
                {
                    std::cout << "Checkmate! Human wins!" << std::endl;
                }
                else
                {
                    std::cout << "Stalemate! It's a draw!" << std::endl;
                }
                window.close();
                continue;
            }

            auto start = std::chrono::high_resolution_clock::now();
            Move bestMove = ai.findBestMove(board);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;

            board.makeMove(bestMove);

            std::cout << "Nodes visited: " << ai.getNodesVisited() << " AI plays: " << moveToString(bestMove) << " Time taken: " << duration.count() << " ms" << std::endl;
            
            board.printBoard();
            
            switchPlayer();

            std::vector<Move> humanMoves = MoveGenerator::generateMoves(board, humanPlayer);
            if (humanMoves.empty())
            {
                if (MoveGenerator::isKingInCheck(board, humanPlayer))
                {
                    std::cout << "Checkmate! AI wins!" << std::endl;
                }
                else
                {
                    std::cout << "Stalemate! It's a draw!" << std::endl;
                }
                window.close();
                continue;
            }

            pieceSelected = false;
            selectedRow = -1;
            selectedCol = -1;
        }

        // 2. Obsługa eventów SFML 3
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButton->button != sf::Mouse::Button::Left)
                {
                    continue;
                }

                if (currentPlayer != humanPlayer)
                {
                    continue;
                }

                float squareSize = window.getSize().x / 8.0f;

                int screenCol = static_cast<int>(mouseButton->position.x / squareSize);
                int screenRow = static_cast<int>(mouseButton->position.y / squareSize);

                int boardCol = screenCol;
                int boardRow = 7 - screenRow;

                if (!board.isInsideBoard(boardRow, boardCol))
                {
                    continue;
                }

                if (!pieceSelected)
                {
                    // pobierz figurę
                    // jeśli należy do currentPlayer:
                    //     zapamiętaj selectedRow, selectedCol
                    //     pieceSelected = true
                    Piece piece = board.getPiece(boardRow, boardCol);
                    if (piece.isEmpty() || piece.color != currentPlayer)
                    {
                        continue;
                    }
                    selectedRow = boardRow;
                    selectedCol = boardCol;
                    pieceSelected = true;

                }
                else
                {
                    // utwórz Move(selectedRow, selectedCol, boardRow, boardCol)
                    // jeśli isMoveLegal(move):
                    //     board.makeMove(move)
                    //     switchPlayer()
                    //
                    // niezależnie od wyniku:
                    //     pieceSelected = false

                    Move move(selectedRow, selectedCol, boardRow, boardCol);
                    if (isMoveLegal(move))
                    {
                        board.makeMove(move);
                        switchPlayer();
                    }
                    pieceSelected = false;
                }
            }
        }

        window.clear();
        renderer.draw(window, board);
        window.display();
    }
}