#pragma once

#include "defines.hpp"

class ChessBoard
{
public:
    void initBoard()
    {
        for (short i = 0; i < 8; i++)
        {
            state[i] = new short[8];
            for (short j = 0; j < 8; j++)
            {
                state[i][j] = 0;
            }
        }
    }

    short getPieceFrom(char letter, short index)
    {
        short let = letter - 'a';
        return state[let][index];
    }

    void putPieceTo(char letter, short index, short piece)
    {
        short let = letter - 'a';
        state[let][index] = piece;

        if (piece == WHITE_KING)
        {
            whiteKingLetter = let;
            whiteKingIndex = index;
            whiteKingHasMoved = true;
        }
        if (piece == BLACK_KING)
        {
            blackKingLetter = let;
            blackKingIndex = index;
            blackKingHasMoved = true;
        }
    }

    void removePieceFrom(char letter, short index)
    {
        short let = letter - 'a';
        state[let][index] = 0;
    }

    short *getKingCords(bool white)
    {
        short *result = new short[2];
        if (white)
        {
            result[0] = whiteKingLetter + 'a';
            result[1] = whiteKingIndex;
        }
        else
        {
            result[0] = blackKingLetter + 'a';
            result[1] = blackKingIndex;
        }

        return result;
    }

private:
    short **state = new short *[8];
    short whiteKingLetter = 4;
    short whiteKingIndex = 0;
    short blackKingLetter = 4;
    short blackKingIndex = 7;
    bool whiteKingHasMoved = false;
    bool blackKingHasMoved = false;
};
