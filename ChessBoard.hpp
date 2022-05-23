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
        whiteKingHasMoved = false;
        blackKingHasMoved = false;
        rightWhiteRookHasMoved = false;
        leftWhiteRookHasMoved = false;
        rightBlackRookHasMoved = false;
        leftBlackRookHasMoved = false;
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
        }
        if (piece == BLACK_KING)
        {
            blackKingLetter = let;
            blackKingIndex = index;
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

    bool isPossibleCastling(bool white, bool right)
    {
        if (white)
        {
            if (!whiteKingHasMoved)
            {
                if (right)
                {
                    return getPieceFrom('f', 0) == 0 &&
                           getPieceFrom('g', 0) == 0 &&
                           !rightWhiteRookHasMoved;
                }
                return getPieceFrom('d', 0) == 0 &&
                       getPieceFrom('c', 0) == 0 &&
                       getPieceFrom('b', 0) == 0 &&
                       !leftWhiteRookHasMoved;
            }
            else
                return false;
        }

        if (!blackKingHasMoved)
        {
            if (right)
            {
                return getPieceFrom('f', 7) == 0 &&
                       getPieceFrom('g', 7) == 0 &&
                       !rightBlackRookHasMoved;
            }
            return getPieceFrom('d', 7) == 0 &&
                   getPieceFrom('c', 7) == 0 &&
                   getPieceFrom('b', 7) == 0 &&
                   !leftBlackRookHasMoved;
        }

        return false;
    }

    void checkState()
    {
        leftWhiteRookHasMoved = getPieceFrom('a', 0) != WHITE_ROOK || leftWhiteRookHasMoved;
        rightWhiteRookHasMoved = getPieceFrom('h', 0) != WHITE_ROOK || rightWhiteRookHasMoved;
        leftBlackRookHasMoved = getPieceFrom('a', 7) != BLACK_ROOK || leftBlackRookHasMoved;
        rightBlackRookHasMoved = getPieceFrom('h', 7) != BLACK_ROOK || rightBlackRookHasMoved;
        whiteKingHasMoved = getPieceFrom('e', 0) != WHITE_KING || whiteKingHasMoved;
        blackKingHasMoved = getPieceFrom('e', 7) != BLACK_KING || blackKingHasMoved;
    }

private:
    short **state = new short *[8];
    short whiteKingLetter = 4;
    short whiteKingIndex = 0;
    short blackKingLetter = 4;
    short blackKingIndex = 7;
    bool whiteKingHasMoved;
    bool blackKingHasMoved;
    bool rightWhiteRookHasMoved;
    bool leftWhiteRookHasMoved;
    bool rightBlackRookHasMoved;
    bool leftBlackRookHasMoved;
};
