#ifndef EVALUATOR_H
#define EVALUATOR_H

#pragma once

#include "Board.h"

class Evaluator
{
public:
    static int evaluateBoard(const Board& board);

private:
    static int getPieceValue(PieceType type);

};

#endif