#include "AI.h"
#include <algorithm>
#include <iostream>
#include "Evaluator.h"
#include <limits>

AI::AI(PieceColor color, int depth) : aiColor(color), searchDepth(depth), nodesVisited(0) {}

Move AI::findBestMove(Board& board)
{
    nodesVisited = 0;
    Move bestMove(0, 0, 0, 0);
    int bestValue = (aiColor == PieceColor::White) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    std::vector<Move> legalMoves = MoveGenerator::generateMoves(board, aiColor);
    for (const Move& move : legalMoves)
    {
        Piece capturedPiece = board.makeMove(move);
        int moveValue = minimax(board, searchDepth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), (aiColor == PieceColor::White) ? PieceColor::Black : PieceColor::White);
        board.undoMove(move, capturedPiece);

        if ((aiColor == PieceColor::White && moveValue > bestValue) || (aiColor == PieceColor::Black && moveValue < bestValue))
        {
            bestValue = moveValue;
            bestMove = move;
        }
    }

    return bestMove;
}

int AI::getSearchDepth() const
{
    return searchDepth;
}

long long AI::getNodesVisited() const
{
    return nodesVisited;
}

int AI::minimax(Board& board, int depth, int alpha, int beta, PieceColor currentPlayer)
{
    nodesVisited++;

    if (depth == 0)
    {
        return Evaluator::evaluateBoard(board);
    }

    std::vector<Move> legalMoves = MoveGenerator::generateMoves(board, currentPlayer);
    if (legalMoves.empty())
    {
        return Evaluator::evaluateBoard(board);
    }

    int bestValue = (currentPlayer == PieceColor::White) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (const Move& move : legalMoves)
    {
        Piece capturedPiece = board.makeMove(move);
        int moveValue = minimax(board, depth - 1, alpha, beta, (currentPlayer == PieceColor::White) ? PieceColor::Black : PieceColor::White);
        board.undoMove(move, capturedPiece);

        if (currentPlayer == PieceColor::White)
        {
            bestValue = std::max(bestValue, moveValue);
            alpha = std::max(alpha, bestValue);
        }
        else
        {
            bestValue = std::min(bestValue, moveValue);
            beta = std::min(beta, bestValue);
        }

        if (beta <= alpha)
        {
            break; // Alpha-beta pruning
        }
    }

    return bestValue;
}