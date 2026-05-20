#ifndef GAME_H
#define GAME_H

#pragma once
#include "Board.h"
#include "AI.h"


class Game
{
public:
    Game();

    Board board;
    PieceColor currentPlayer;
    PieceColor humanPlayer;
    AI ai;

    void runCommandLineInterface();

private:
    bool parseMove(const std::string& from, const std::string& to, Move& move);
    std::string moveToString(const Move& move);
    void switchPlayer();
    bool isMoveLegal(const Move& move);
};

#endif