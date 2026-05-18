#include "MoveGenerator.h"


std::vector<Move> MoveGenerator::generateMoves(const Board& board, PieceColor color)
{
    std::vector<Move> moves;
    for (int row = 0; row < Board::SIZE; row++)
    {
        for (int col = 0; col < Board::SIZE; col++)
        {
            Piece piece = board.getPiece(row, col);
            if (piece.color == color)
            {
                switch (piece.type)
                {
                    case PieceType::Pawn:
                        generatePawnMoves(board, row, col, color, moves);
                        break;
                    case PieceType::Knight:
                        generateKnightMoves(board, row, col, color, moves);
                        break;
                    case PieceType::Bishop:
                        generateBishopMoves(board, row, col, color, moves);
                        break;
                    case PieceType::Rook:
                        generateRookMoves(board, row, col, color, moves);
                        break;
                    case PieceType::Queen:
                        generateQueenMoves(board, row, col, color, moves);
                        break;
                    case PieceType::King:
                        generateKingMoves(board, row, col, color, moves);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return moves;
}

void MoveGenerator::generatePawnMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves)
{
    int direction = (color == PieceColor::White) ? 1 : -1;
    int startRow = (color == PieceColor::White) ? 1 : 6;

    // Move forward
    if (board.isEmptySquare(row + direction, col))
    {
        moves.emplace_back(Move(row, col, row + direction, col));
        // Double move from starting position
        if (row == startRow && board.isEmptySquare(row + 2 * direction, col))
        {
            moves.emplace_back(Move(row, col, row + 2 * direction, col));
        }
    }

    // Capture diagonally
    for (int dCol = -1; dCol <= 1; dCol += 2)
    {
        if (board.isOpponentPiece(row + direction, col + dCol, color))
        {
            moves.emplace_back(Move(row, col, row + direction, col + dCol));
        }
    }
}

void MoveGenerator::generateKnightMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves)
{
    // Knight move offsets
    const std::vector<std::pair<int, int>> knightOffsets = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    for (const auto& offset : knightOffsets)
    {
        int newRow = row + offset.first;
        int newCol = col + offset.second;
        if (board.isInsideBoard(newRow, newCol) && !board.isOwnPiece(newRow, newCol, color))
        {
            moves.emplace_back(Move(row, col, newRow, newCol));
        }
    }
}

void MoveGenerator::generateBishopMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves)
{
    // Bishop move directions
    const std::vector<std::pair<int, int>> bishopDirections = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (const auto& direction : bishopDirections)
    {
        int newRow = row + direction.first;
        int newCol = col + direction.second;
        while (board.isInsideBoard(newRow, newCol))
        {
            if (board.isEmptySquare(newRow, newCol))
            {
                moves.emplace_back(Move(row, col, newRow, newCol));
            }
            else
            {
                if (board.isOpponentPiece(newRow, newCol, color))
                {
                    moves.emplace_back(Move(row, col, newRow, newCol));
                }
                break; // Stop if we hit a piece
            }
            newRow += direction.first;
            newCol += direction.second;
        }
    }
}

void MoveGenerator::generateRookMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves)
{
    // Rook move directions
    const std::vector<std::pair<int, int>> rookDirections = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    for (const auto& direction : rookDirections)
    {
        int newRow = row + direction.first;
        int newCol = col + direction.second;
        while (board.isInsideBoard(newRow, newCol))
        {
            if (board.isEmptySquare(newRow, newCol))
            {
                moves.emplace_back(Move(row, col, newRow, newCol));
            }
            else
            {
                if (board.isOpponentPiece(newRow, newCol, color))
                {
                    moves.emplace_back(Move(row, col, newRow, newCol));
                }
                break; // Stop if we hit a piece
            }
            newRow += direction.first;
            newCol += direction.second;
        }
    }
}

void MoveGenerator::generateQueenMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves)
{
    generateRookMoves(board, row, col, color, moves);
    generateBishopMoves(board, row, col, color, moves);
}

void MoveGenerator::generateKingMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves)
{
    // King move offsets
    const std::vector<std::pair<int, int>> kingOffsets = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };

    for (const auto& offset : kingOffsets)
    {
        int newRow = row + offset.first;
        int newCol = col + offset.second;
        if (board.isInsideBoard(newRow, newCol) && !board.isOwnPiece(newRow, newCol, color))
        {
            moves.emplace_back(Move(row, col, newRow, newCol));
        }
    }
}
