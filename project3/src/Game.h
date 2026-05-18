#ifndef GAME_H
#define GAME_H

#pragma once
#include "Board.h"


class Game
{
public:
    Game();

    Board board;
    PieceColor currentPlayer;
    
    void runCommandLineInterface();

private:
    bool parseMove(const std::string& from, const std::string& to, Move& move);
    void switchPlayer();
    bool isMoveLegal(const Move& move);
};

#endif