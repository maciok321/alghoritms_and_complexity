#include "Board.h"
#include <iostream>

Board::Board()
{
    setupInitialPosition();
}

void Board::setupInitialPosition()
{
    // Clear the board
    for (int row = 0; row < SIZE; row++)
        for (int col = 0; col < SIZE; col++)
            board[row][col] = Piece();
    
    // Initialize the board with the standard chess starting position
    // Pawns
    for (int col = 0; col < SIZE; col++)
    {
        board[1][col] = Piece(PieceType::Pawn, PieceColor::White);
        board[6][col] = Piece(PieceType::Pawn, PieceColor::Black);
    }

    // Rooks
    board[0][0] = board[0][7] = Piece(PieceType::Rook, PieceColor::White);
    board[7][0] = board[7][7] = Piece(PieceType::Rook, PieceColor::Black);

    // Knights
    board[0][1] = board[0][6] = Piece(PieceType::Knight, PieceColor::White);
    board[7][1] = board[7][6] = Piece(PieceType::Knight, PieceColor::Black);

    // Bishops
    board[0][2] = board[0][5] = Piece(PieceType::Bishop, PieceColor::White);
    board[7][2] = board[7][5] = Piece(PieceType::Bishop, PieceColor::Black);

    // Queens
    board[0][3] = Piece(PieceType::Queen, PieceColor::White);
    board[7][3] = Piece(PieceType::Queen, PieceColor::Black);

    // Kings
    board[0][4] = Piece(PieceType::King, PieceColor::White);
    board[7][4] = Piece(PieceType::King, PieceColor::Black);
}

Piece Board::getPiece(int row, int col) const
{
    return board[row][col];
}

void Board::setPiece(int row, int col, const Piece& piece)
{
    board[row][col] = piece;
}

Piece Board::makeMove(const Move& move)
{
    Piece capturedPiece = getPiece(move.toRow, move.toCol);
    Piece piece = getPiece(move.fromRow, move.fromCol);
    setPiece(move.toRow, move.toCol, piece);
    setPiece(move.fromRow, move.fromCol, Piece());
    return capturedPiece;
}

void Board::undoMove(const Move& move, Piece capturedPiece)
{
    Piece piece = getPiece(move.toRow, move.toCol);
    setPiece(move.fromRow, move.fromCol, piece);
    setPiece(move.toRow, move.toCol, capturedPiece);
}

bool Board::isInsideBoard(int row, int col) const
{
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

bool Board::isEmptySquare(int row, int col) const
{
    return isInsideBoard(row, col) && getPiece(row, col).isEmpty();
}

bool Board::isOpponentPiece(int row, int col, PieceColor color) const
{
    return isInsideBoard(row, col) && !getPiece(row, col).isEmpty() && getPiece(row, col).color != color;
}

bool Board::isOwnPiece(int row, int col, PieceColor color) const
{
    return isInsideBoard(row, col) && !getPiece(row, col).isEmpty() && getPiece(row, col).color == color;
}

void Board::printBoard() const
{
    for (int row = 7; row >= 0; row--)
    {
        std::cout << row + 1 << " ";
        for (int col = 0; col < SIZE; col++)
        {
            const Piece& piece = board[row][col];
            char symbol = '.';
            if (!piece.isEmpty())
            {
                switch (piece.type)
                {
                    case PieceType::Pawn:   symbol = 'P'; break;
                    case PieceType::Knight: symbol = 'N'; break;
                    case PieceType::Bishop: symbol = 'B'; break;
                    case PieceType::Rook:   symbol = 'R'; break;
                    case PieceType::Queen:  symbol = 'Q'; break;
                    case PieceType::King:   symbol = 'K'; break;
                    default: break;
                }
                if (piece.color == PieceColor::Black)
                    symbol = tolower(symbol);
            }
            std::cout << symbol << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "  A B C D E F G H" << std::endl;
}