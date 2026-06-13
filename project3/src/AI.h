#ifndef AI_H
#define AI_H

#pragma once
#include "Board.h"
#include "Move.h"
#include "MoveGenerator.h"
#include "Evaluator.h"
#include <string>
#include <vector>

class AI
{
public:
    AI(PieceColor color, int depth);
    PieceColor aiColor;

    Move findBestMove(Board& board);

    int getSearchDepth() const;
    long long getNodesVisited() const;

private:
    int searchDepth;
    long long nodesVisited;
    const int CHECKMATE_SCORE = 1000000;

    int minimax(Board& board, int depth, int alpha, int beta, PieceColor currentPlayer);
};

#endif