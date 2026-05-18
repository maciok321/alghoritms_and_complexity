#pragma once

enum class PieceType
{
    None,
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

enum class PieceColor
{
    None,
    White,
    Black
};

struct Piece
{
    PieceType type;
    PieceColor color;

    Piece() : type(PieceType::None), color(PieceColor::None) {}
    Piece(PieceType t, PieceColor c) : type(t), color(c) {}

    bool isEmpty() const { return type == PieceType::None; }
};

inline PieceColor oppositeColor(PieceColor color)
{
    if (color == PieceColor::White) return PieceColor::Black;
    if (color == PieceColor::Black) return PieceColor::White;
    return PieceColor::None;
}