#include "Game.h"
#include <iostream>
#include <string>
#include "MoveGenerator.h"
#include <algorithm>
#include <sstream>

Game::Game() : currentPlayer(PieceColor::White){}

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
        std::cout << (currentPlayer == PieceColor::White ? "White" : "Black") << "'s turn. Enter your move (e.g., e2 e4), or 'exit': ";

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