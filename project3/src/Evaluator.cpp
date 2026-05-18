#include "Evaluator.h"
#include "Board.h"

int Evaluator::evaluateBoard(const Board& board)
{
    int totalEvaluation = 0;

    for (int row = 0; row < Board::SIZE; ++row)
    {
        for (int col = 0; col < Board::SIZE; ++col)
        {
            Piece piece = board.getPiece(row, col);
            if (piece.color == PieceColor::White)
            {
                totalEvaluation += getPieceValue(piece.type);
            }
            else if (piece.color == PieceColor::Black)
            {
                totalEvaluation -= getPieceValue(piece.type);
            }
        }
    }

    return totalEvaluation;
}

int Evaluator::getPieceValue(PieceType type)
{
    switch (type)
    {
    case PieceType::Pawn:   return 100;
    case PieceType::Knight: return 300;
    case PieceType::Bishop: return 300;
    case PieceType::Rook:   return 500;
    case PieceType::Queen:  return 900;
    case PieceType::King:   return 20000;
    default:               return 0;
    }
}