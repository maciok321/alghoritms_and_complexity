#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

Renderer::Renderer()
{
    if(!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) // Załaduj font tylko raz
    {
        std::cerr << "Failed to load font!" << std::endl;
    }
}

char Renderer::pieceToChar(const Piece& piece) const
{
    switch (piece.type)
    {
        case PieceType::Pawn:   return piece.color == PieceColor::White ? 'P' : 'p';
        case PieceType::Knight: return piece.color == PieceColor::White ? 'N' : 'n';
        case PieceType::Bishop: return piece.color == PieceColor::White ? 'B' : 'b';
        case PieceType::Rook:   return piece.color == PieceColor::White ? 'R' : 'r';
        case PieceType::Queen:  return piece.color == PieceColor::White ? 'Q' : 'q';
        case PieceType::King:   return piece.color == PieceColor::White ? 'K' : 'k';
        default: return '?';
    }
}

void Renderer::draw(sf::RenderWindow& window, const Board& board)
{
    squareSize = window.getSize().x / 8.0f;

    for (int screenRow = 0; screenRow < 8; ++screenRow)
    {
        for (int screenCol = 0; screenCol < 8; ++screenCol)
        {
            int boardRow = 7 - screenRow;
            int boardCol = screenCol;

            // Rysuj pole
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
            square.setPosition({screenCol * squareSize, screenRow * squareSize});
            bool isWhite = (screenRow + screenCol) % 2 == 0;
            square.setFillColor(isWhite ? sf::Color(240, 217, 181) : sf::Color(181, 136, 99));
            window.draw(square);

            // Rysuj figurę jako literę
            Piece piece = board.getPiece(boardRow, boardCol);
            if (piece.type != PieceType::None)
            {
                char letter = pieceToChar(piece);
                sf::Text text(font);
                text.setString(std::string(1, letter));
                text.setCharacterSize(static_cast<unsigned int>(squareSize * 0.6f));
                text.setFillColor(piece.color == PieceColor::White ? sf::Color::White : sf::Color::Black);
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});
                text.setPosition({screenCol * squareSize + squareSize / 2.0f, screenRow * squareSize + squareSize / 2.0f});
                window.draw(text);
            }
        }
    }
}