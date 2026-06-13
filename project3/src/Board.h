#ifndef BOARD_H
#define BOARD_H

#pragma once

#include <array>
#include "Piece.h"
#include "Move.h"

struct MoveState
{
    Piece capturedPiece;
    Piece movedPiece;
};

class Board
{
    
public:
    static const int SIZE = 8;
    
    Board();
    
    void setupInitialPosition();
    
    Piece getPiece(int row, int col) const;
    void setPiece(int row, int col, const Piece& piece);
    
    bool isInsideBoard(int row, int col) const;
    bool isEmptySquare(int row, int col) const;
    bool isOpponentPiece(int row, int col, PieceColor color) const;
    bool isOwnPiece(int row, int col, PieceColor color) const;
    
    MoveState makeMove(const Move& move);
    void undoMove(const Move& move, const MoveState& state);
    
    void printBoard() const;
    
    Piece findKingPosition(PieceColor color, int& kingRow, int& kingCol) const;
private:
    std::array<std::array<Piece, SIZE>, SIZE> board;
};

#endif