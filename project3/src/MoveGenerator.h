#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#pragma once
#include "Board.h"
#include "Move.h"
#include "Piece.h"
#include <vector>

class MoveGenerator
{
public:
    static std::vector<Move> generateMoves(Board& board, PieceColor color);
    static bool isKingInCheck(const Board& board, PieceColor color);
    
    private:
    static std::vector<Move> generatePseudoLegalMoves(const Board& board, PieceColor color);
    static void generatePawnMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves);
    static void generateKnightMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves);
    static void generateBishopMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves);
    static void generateRookMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves);
    static void generateQueenMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves);
    static void generateKingMoves(const Board& board, int row, int col, PieceColor color, std::vector<Move>& moves);


};

#endif