#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

Renderer::Renderer()
{
    loadTextures();
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

            if (!piece.isEmpty())
            {
                std::string key = getTextureKey(piece);
                sf::Sprite sprite(pieceTextures.at(key));

                float scaleX = squareSize / sprite.getTexture().getSize().x;
                float scaleY = squareSize / sprite.getTexture().getSize().y;

                sprite.setScale({scaleX, scaleY});
                sprite.setPosition({screenCol * squareSize, screenRow * squareSize});

                window.draw(sprite);
            }
        }
    }
}


std::string Renderer::getTextureKey(const Piece& piece) const
{
    std::string colorPrefix = (piece.color == PieceColor::White) ? "white_" : "black_";
    std::string typeName;

    switch (piece.type)
    {
        case PieceType::Pawn:   typeName = "pawn"; break;
        case PieceType::Knight: typeName = "knight"; break;
        case PieceType::Bishop: typeName = "bishop"; break;
        case PieceType::Rook:   typeName = "rook"; break;
        case PieceType::Queen:  typeName = "queen"; break;
        case PieceType::King:   typeName = "king"; break;
        default: return "";
    }

    return colorPrefix + typeName;
}


void Renderer::loadTextures()
{
    std::string basePath = "../assets/"; // Ścieżka do katalogu z teksturami
    std::vector<std::string> pieceTypes = {"pawn", "knight", "bishop", "rook", "queen", "king"};
    std::vector<std::string> colors = {"white", "black"};

    for (const auto& color : colors)
    {
        for (const auto& type : pieceTypes)
        {
            std::string key = color + "_" + type;
            std::string filePath = basePath + key + ".png";
            sf::Texture texture;
            if (!texture.loadFromFile(filePath))
            {
                std::cerr << "Failed to load texture: " << filePath << std::endl;
                continue;
            }
            pieceTextures[key] = texture;
        }
    }
}