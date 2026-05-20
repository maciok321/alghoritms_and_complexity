#pragma once
#include <iostream>

struct Move{
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;

    Move(int fr, int fc, int tr, int tc) : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc) {}

    bool operator==(const Move& other) const {
        return fromRow == other.fromRow && fromCol == other.fromCol &&
               toRow == other.toRow && toCol == other.toCol;
    }

    friend std::ostream& operator<<(std::ostream& os, const Move& move) {
        os << "(" << move.fromRow + 1 << ", " << move.fromCol + 1 << ") to ("
           << move.toRow + 1 << ", " << move.toCol + 1 << ")";
        return os;
    }
};