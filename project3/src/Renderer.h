#ifndef RENDERER_H
#define RENDERER_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include <map>

class Renderer
{
public:
    Renderer();

    void draw(sf::RenderWindow& window, const Board& board);

private:
    float squareSize;
    std::map<std::string, sf::Texture> pieceTextures;

    sf::Font font;
    char pieceToChar(const Piece& piece) const;

};

#endif