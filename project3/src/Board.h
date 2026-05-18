#ifndef BOARD_H
#define BOARD_H

#pragma once

#include <array>
#include "Piece.h"
#include "Move.h"

class Board
{
private:
    static const int SIZE = 8;
    std::array<std::array<Piece, SIZE>, SIZE> board;

public:
    Board();

    void setupInitialPosition();

    Piece getPiece(int row, int col) const;
    void setPiece(int row, int col, const Piece& piece);

    bool isInsideBoard(int row, int col) const;
    bool isEmptySquare(int row, int col) const;
    bool isOpponentPiece(int row, int col, PieceColor color) const;
    bool isOwnPiece(int row, int col, PieceColor color) const;

    void makeMove(const Move& move);
    void undoMove(const Move& move, Piece capturedPiece);

    void printBoard() const;
};

#endif