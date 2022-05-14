#pragma once

#include "defines.hpp"
#include <vector>
#include "ChessBoard.hpp"

class ChessArbiter
{
public:
    ChessArbiter() {}
    void startGame()
    {
        isWhiteMove = true;

        board.initBoard();

        board.putPieceTo('a', 0, WHITE_ROOK);
        board.putPieceTo('b', 0, WHITE_KNIGHT);
        board.putPieceTo('c', 0, WHITE_BISHOP);
        board.putPieceTo('d', 0, WHITE_QUEEN);
        board.putPieceTo('e', 0, WHITE_KING);
        board.putPieceTo('f', 0, WHITE_BISHOP);
        board.putPieceTo('g', 0, WHITE_KNIGHT);
        board.putPieceTo('h', 0, WHITE_ROOK);

        board.putPieceTo('a', 7, BLACK_ROOK);
        board.putPieceTo('b', 7, BLACK_KNIGHT);
        board.putPieceTo('c', 7, BLACK_BISHOP);
        board.putPieceTo('d', 7, BLACK_QUEEN);
        board.putPieceTo('e', 7, BLACK_KING);
        board.putPieceTo('f', 7, BLACK_BISHOP);
        board.putPieceTo('g', 7, BLACK_KNIGHT);
        board.putPieceTo('h', 7, BLACK_ROOK);

        for (char letter = 'a'; letter <= 'h'; letter++)
        {
            board.putPieceTo(letter, 1, WHITE_PAWN);
            board.putPieceTo(letter, 6, BLACK_PAWN);
        }

        numberOfPossibleMoves = 0;
        selectedLetter = 0;
        selectedIndex = -1;
    }

    bool isRightColor(short piece)
    {
        return (piece > 0 && isWhiteMove) || (piece < 0 && !isWhiteMove);
    }

    bool isSameColor(short piece1, short piece2)
    {
        return (piece1 > 0 && piece2 > 0) || (piece1 < 0 && piece2 < 0);
    }

    bool isCorrectCords(char letter, short index)
    {
        short let = letter - 'a';
        return (let >= 0) && (let < 8) && (index >= 0) && (index < 8);
    }

    void moveTo(char letter, short index)
    {
        short pieceFrom = board.getPieceFrom(selectedLetter, selectedIndex);
        board.removePieceFrom(selectedLetter, selectedIndex);
        board.removePieceFrom(letter, index);
        board.putPieceTo(letter, index, pieceFrom);
        isWhiteMove = !isWhiteMove;
        numberOfPossibleMoves = 0;

        removeSelect();
    }

    bool selectPiece(char letter, short index)
    {
        short pieceFrom = board.getPieceFrom(letter, index);
        if (pieceFrom != 0)
        {
            if (isRightColor(pieceFrom))
            {
                selectedLetter = letter;
                selectedIndex = index;
                return true;
            }
        }
        return false;
    }

    short **getPossibleMoves()
    {
        short **result;

        short piece = board.getPieceFrom(selectedLetter, selectedIndex);
        switch (abs(piece))
        {
        case WHITE_PAWN:
            result = getPossiblePawnMoves(piece);
            break;
        case WHITE_ROOK:
            result = getPossibleRookMoves();
            break;
        case WHITE_KNIGHT:
            result = getPossibleKnightMoves();
            break;
        case WHITE_BISHOP:
            result = getPossibleBishopMoves();
            break;
        case WHITE_QUEEN:
            result = getPossibleQueenMoves();
            break;
        case WHITE_KING:
            result = getPossibleKingMoves();
            break;

        default:
            result = nullptr;
            break;
        }

        // result = removeChecks(result);

        return result;
    }

    short **getPossiblePawnMoves(short piece)
    {
        bool isWhitePiece = piece > 0;
        std::vector<std::vector<short>> tempResult;
        std::vector<short> temp(2);
        short tempPiece;

        if (isWhitePiece)
        {
            if (selectedIndex + 1 < 8)
            {
                tempPiece = board.getPieceFrom(selectedLetter, selectedIndex + 1);
                if (tempPiece == 0)
                {
                    temp.at(0) = selectedLetter - 'a';
                    temp.at(1) = selectedIndex + 1;
                    tempResult.push_back(temp);

                    if (selectedIndex == 1)
                    {
                        tempPiece = board.getPieceFrom(selectedLetter, selectedIndex + 2);
                        if (tempPiece == 0)
                        {
                            temp.at(0) = selectedLetter - 'a';
                            temp.at(1) = selectedIndex + 2;
                            tempResult.push_back(temp);
                        }
                    }
                }
            }

            if (selectedLetter - 'a' - 1 >= 0 && selectedIndex + 1 < 8)
                if (board.getPieceFrom(selectedLetter - 1, selectedIndex + 1) < 0)
                {
                    temp.at(0) = selectedLetter - 'a' - 1;
                    temp.at(1) = selectedIndex + 1;
                    tempResult.push_back(temp);
                }

            if (selectedLetter - 'a' + 1 < 8 && selectedIndex + 1 < 8)
                if (board.getPieceFrom(selectedLetter + 1, selectedIndex + 1) < 0)
                {
                    temp.at(0) = selectedLetter - 'a' + 1;
                    temp.at(1) = selectedIndex + 1;
                    tempResult.push_back(temp);
                }
        }
        else
        {
            if (selectedIndex - 1 >= 0)
            {
                tempPiece = board.getPieceFrom(selectedLetter, selectedIndex - 1);
                if (tempPiece == 0)
                {
                    temp.at(0) = selectedLetter - 'a';
                    temp.at(1) = selectedIndex - 1;
                    tempResult.push_back(temp);
                    if (selectedIndex == 6)
                    {
                        tempPiece = board.getPieceFrom(selectedLetter, selectedIndex - 2);
                        if (tempPiece == 0)
                        {
                            temp.at(0) = selectedLetter - 'a';
                            temp.at(1) = selectedIndex - 2;
                            tempResult.push_back(temp);
                        }
                    }
                }
            }

            if (selectedLetter - 'a' - 1 >= 0 && selectedIndex - 1 >= 0)
                if (board.getPieceFrom(selectedLetter - 1, selectedIndex - 1) > 0)
                {
                    temp.at(0) = selectedLetter - 'a' - 1;
                    temp.at(1) = selectedIndex - 1;
                    tempResult.push_back(temp);
                }

            if (selectedLetter - 'a' + 1 < 8 && selectedIndex - 1 >= 0)
                if (board.getPieceFrom(selectedLetter + 1, selectedIndex - 1) > 0)
                {
                    temp.at(0) = selectedLetter - 'a' + 1;
                    temp.at(1) = selectedIndex - 1;
                    tempResult.push_back(temp);
                }
        }

        numberOfPossibleMoves = tempResult.size();
        short **result = new short *[numberOfPossibleMoves];
        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            result[i] = new short[2];
            result[i][0] = tempResult.at(i).at(0);
            result[i][1] = tempResult.at(i).at(1);
        }

        return result;
    }

    short **getPossibleRookMoves()
    {
        std::vector<std::vector<short>> tempResult;
        std::vector<short> temp(2);
        short tempPiece;

        for (short i = selectedLetter - 'a' - 1; i >= 0; i--)
        {
            tempPiece = board.getPieceFrom('a' + i, selectedIndex);
            if (tempPiece != 0)
            {
                bool isWhiteTempPiece = tempPiece > 0;
                if (isWhiteTempPiece != isWhiteMove)
                {
                    temp.at(0) = i;
                    temp.at(1) = selectedIndex;
                    tempResult.push_back(temp);
                }
                break;
            }
            else
            {
                temp.at(0) = i;
                temp.at(1) = selectedIndex;
                tempResult.push_back(temp);
            }
        }

        for (short i = selectedLetter - 'a' + 1; i < 8; i++)
        {
            tempPiece = board.getPieceFrom('a' + i, selectedIndex);
            if (tempPiece != 0)
            {
                bool isWhiteTempPiece = tempPiece > 0;
                if (isWhiteTempPiece != isWhiteMove)
                {
                    temp.at(0) = i;
                    temp.at(1) = selectedIndex;
                    tempResult.push_back(temp);
                    break;
                }
                else
                    break;
            }
            else
            {
                temp.at(0) = i;
                temp.at(1) = selectedIndex;
                tempResult.push_back(temp);
            }
        }

        for (short i = selectedIndex - 1; i >= 0; i--)
        {
            tempPiece = board.getPieceFrom(selectedLetter, i);
            if (tempPiece != 0)
            {
                bool isWhiteTempPiece = tempPiece > 0;
                if (isWhiteTempPiece != isWhiteMove)
                {
                    temp.at(0) = selectedLetter - 'a';
                    temp.at(1) = i;
                    tempResult.push_back(temp);
                    break;
                }
                else
                    break;
            }
            else
            {
                temp.at(0) = selectedLetter - 'a';
                temp.at(1) = i;
                tempResult.push_back(temp);
            }
        }

        for (short i = selectedIndex + 1; i < 8; i++)
        {
            tempPiece = board.getPieceFrom(selectedLetter, i);
            if (tempPiece != 0)
            {
                bool isWhiteTempPiece = tempPiece > 0;
                if (isWhiteTempPiece != isWhiteMove)
                {
                    temp.at(0) = selectedLetter - 'a';
                    temp.at(1) = i;
                    tempResult.push_back(temp);
                    break;
                }
                else
                    break;
            }
            else
            {
                temp.at(0) = selectedLetter - 'a';
                temp.at(1) = i;
                tempResult.push_back(temp);
            }
        }

        numberOfPossibleMoves = tempResult.size();
        short **result = new short *[numberOfPossibleMoves];
        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            result[i] = new short[2];
            result[i][0] = tempResult.at(i).at(0);
            result[i][1] = tempResult.at(i).at(1);
        }

        return result;
    }

    short **getPossibleKnightMoves()
    {
        short moves[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

        std::vector<std::vector<short>> tempResult;
        std::vector<short> temp(2);
        short tempPiece;

        for (short i = 0; i < 8; i++)
        {
            short letter = selectedLetter + moves[i][0];
            short index = selectedIndex + moves[i][1];
            if (isCorrectCords(letter, index))
            {
                tempPiece = board.getPieceFrom(letter, index);
                if (tempPiece != 0)
                {
                    bool isWhiteTempPiece = tempPiece > 0;
                    if (isWhiteMove != isWhiteTempPiece)
                    {
                        temp.at(0) = letter - 'a';
                        temp.at(1) = index;
                        tempResult.push_back(temp);
                    }
                }
                else
                {
                    temp.at(0) = letter - 'a';
                    temp.at(1) = index;
                    tempResult.push_back(temp);
                }
            }
        }

        numberOfPossibleMoves = tempResult.size();
        short **result = new short *[numberOfPossibleMoves];
        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            result[i] = new short[2];
            result[i][0] = tempResult.at(i).at(0);
            result[i][1] = tempResult.at(i).at(1);
        }

        return result;
    }

    short **getPossibleBishopMoves()
    {
        std::vector<std::vector<short>> tempResult;
        std::vector<short> temp(2);
        short tempPiece;

        for (short i = selectedLetter - 'a' - 1; i >= 0; i--)
        {
            short letter = i + 'a';
            short index = selectedIndex - (selectedLetter - 'a' - i);
            if (isCorrectCords(letter, index))
            {
                tempPiece = board.getPieceFrom(letter, index);
                if (tempPiece != 0)
                {
                    bool isWhiteTempPiece = tempPiece > 0;
                    if (isWhiteMove != isWhiteTempPiece)
                    {
                        temp.at(0) = letter - 'a';
                        temp.at(1) = index;
                        tempResult.push_back(temp);
                    }
                    break;
                }
                else
                {
                    temp.at(0) = letter - 'a';
                    temp.at(1) = index;
                    tempResult.push_back(temp);
                }
            }
            else
                break;
        }

        for (short i = selectedLetter - 'a' - 1; i >= 0; i--)
        {
            short letter = i + 'a';
            short index = selectedIndex + (selectedLetter - 'a' - i);
            if (isCorrectCords(letter, index))
            {
                tempPiece = board.getPieceFrom(letter, index);
                if (tempPiece != 0)
                {
                    bool isWhiteTempPiece = tempPiece > 0;
                    if (isWhiteMove != isWhiteTempPiece)
                    {
                        temp.at(0) = letter - 'a';
                        temp.at(1) = index;
                        tempResult.push_back(temp);
                    }
                    break;
                }
                else
                {
                    temp.at(0) = letter - 'a';
                    temp.at(1) = index;
                    tempResult.push_back(temp);
                }
            }
        }

        for (short i = selectedLetter - 'a' + 1; i < 8; i++)
        {
            short letter = i + 'a';
            short index = selectedIndex - (i - (selectedLetter - 'a'));
            if (isCorrectCords(letter, index))
            {
                tempPiece = board.getPieceFrom(letter, index);
                if (tempPiece != 0)
                {
                    bool isWhiteTempPiece = tempPiece > 0;
                    if (isWhiteMove != isWhiteTempPiece)
                    {
                        temp.at(0) = letter - 'a';
                        temp.at(1) = index;
                        tempResult.push_back(temp);
                    }
                    break;
                }
                else
                {
                    temp.at(0) = letter - 'a';
                    temp.at(1) = index;
                    tempResult.push_back(temp);
                }
            }
        }

        for (short i = selectedLetter - 'a' + 1; i < 8; i++)
        {
            short letter = i + 'a';
            short index = selectedIndex + (i - (selectedLetter - 'a'));
            if (isCorrectCords(letter, index))
            {
                tempPiece = board.getPieceFrom(letter, index);
                if (tempPiece != 0)
                {
                    bool isWhiteTempPiece = tempPiece > 0;
                    if (isWhiteMove != isWhiteTempPiece)
                    {
                        temp.at(0) = letter - 'a';
                        temp.at(1) = index;
                        tempResult.push_back(temp);
                    }
                    break;
                }
                else
                {
                    temp.at(0) = letter - 'a';
                    temp.at(1) = index;
                    tempResult.push_back(temp);
                }
            }
        }

        numberOfPossibleMoves = tempResult.size();
        short **result = new short *[numberOfPossibleMoves];
        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            result[i] = new short[2];
            result[i][0] = tempResult.at(i).at(0);
            result[i][1] = tempResult.at(i).at(1);
        }

        return result;
    }

    short **getPossibleQueenMoves()
    {
        short **rookMoves = getPossibleRookMoves();
        short numberOfPossibleRookMoves = numberOfPossibleMoves;

        short **bishopMoves = getPossibleBishopMoves();
        short numberOfPossibleBishopMoves = numberOfPossibleMoves;

        numberOfPossibleMoves = numberOfPossibleRookMoves + numberOfPossibleBishopMoves;

        short **result = new short *[numberOfPossibleMoves];

        for (short i = 0; i < numberOfPossibleRookMoves; i++)
        {
            result[i] = new short[2];
            result[i][0] = rookMoves[i][0];
            result[i][1] = rookMoves[i][1];
        }

        for (short i = numberOfPossibleRookMoves; i < numberOfPossibleMoves; i++)
        {
            result[i] = new short[2];
            result[i][0] = bishopMoves[i - numberOfPossibleRookMoves][0];
            result[i][1] = bishopMoves[i - numberOfPossibleRookMoves][1];
        }

        return result;
    }

    short **getPossibleKingMoves()
    {
        short moves[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

        std::vector<std::vector<short>> tempResult;
        std::vector<short> temp(2);
        short tempPiece;

        for (short i = 0; i < 8; i++)
        {
            short letter = selectedLetter + moves[i][0];
            short index = selectedIndex + moves[i][1];
            if (isCorrectCords(letter, index))
            {
                tempPiece = board.getPieceFrom(letter, index);
                if (tempPiece != 0)
                {
                    bool isWhiteTempPiece = tempPiece > 0;
                    if (isWhiteMove != isWhiteTempPiece)
                    {
                        temp.at(0) = letter - 'a';
                        temp.at(1) = index;
                        tempResult.push_back(temp);
                    }
                }
                else
                {
                    temp.at(0) = letter - 'a';
                    temp.at(1) = index;
                    tempResult.push_back(temp);
                }
            }
        }

        numberOfPossibleMoves = tempResult.size();
        short **result = new short *[numberOfPossibleMoves];
        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            result[i] = new short[2];
            result[i][0] = tempResult.at(i).at(0);
            result[i][1] = tempResult.at(i).at(1);
        }

        return result;
    }

    short **removeChecks(short **moves)
    {
        std::vector<std::vector<short>> tempResult;
        std::vector<short> temp(2);
        short curNumberOfPossibleMoves = numberOfPossibleMoves;

        for (short i = 0; i < curNumberOfPossibleMoves; i++)
        {
            if (!willBeCheck(selectedLetter, selectedIndex, moves[i][0] + 'a', moves[i][1]))
            {
                temp.at(0) = moves[i][0];
                temp.at(1) = moves[i][1];
                tempResult.push_back(temp);
            }
        }

        numberOfPossibleMoves = tempResult.size();
        short **result = new short *[numberOfPossibleMoves];
        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            result[i] = new short[2];
            result[i][0] = tempResult.at(i).at(0);
            result[i][1] = tempResult.at(i).at(1);
        }

        return result;
    }

    bool willBeCheck(char fromLetter, short fromIndex, char toLetter, short toIndex)
    {
        bool result = false;
        short fromPiece = board.getPieceFrom(fromLetter, fromIndex);
        short tempPiece = board.getPieceFrom(toLetter, toIndex);
        board.removePieceFrom(fromLetter, fromIndex);
        board.removePieceFrom(toLetter, toIndex);
        board.putPieceTo(toLetter, toIndex, fromPiece);

        if (isCheck())
            result = true;

        board.removePieceFrom(toLetter, toIndex);
        board.putPieceTo(fromLetter, fromIndex, fromPiece);
        board.putPieceTo(toLetter, toIndex, tempPiece);

        return result;
    }

    bool isCheck()
    {
        bool result = false;

        short *kingCords = board.getKingCords(isWhiteMove);
        char curSelectedLetter = selectedLetter;
        short curSelectedIndex = selectedIndex;
        selectPiece(kingCords[0], kingCords[1]);

        short **possibleMoves = getPossibleRookMoves();
        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            short tempPiece = board.getPieceFrom(possibleMoves[i][0] + 'a', possibleMoves[i][1]);
            if (isWhiteMove)
            {
                if (tempPiece == BLACK_ROOK || tempPiece == BLACK_QUEEN)
                {
                    result = true;
                }
            }
            else
            {
                if (tempPiece == WHITE_ROOK || tempPiece == WHITE_QUEEN)
                {
                    result = true;
                }
            }
        }

        possibleMoves = getPossibleBishopMoves();
        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            short tempPiece = board.getPieceFrom(possibleMoves[i][0] + 'a', possibleMoves[i][1]);
            if (isWhiteMove)
            {
                if (tempPiece == BLACK_BISHOP || tempPiece == BLACK_QUEEN)
                {
                    result = true;
                }
            }
            else
            {
                if (tempPiece == WHITE_BISHOP || tempPiece == WHITE_QUEEN)
                {
                    result = true;
                }
            }
        }

        possibleMoves = getPossibleKnightMoves();
        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            short tempPiece = board.getPieceFrom(possibleMoves[i][0] + 'a', possibleMoves[i][1]);
            if (isWhiteMove)
            {
                if (tempPiece == BLACK_KNIGHT)
                {
                    result = true;
                }
            }
            else
            {
                if (tempPiece == WHITE_KNIGHT)
                {
                    result = true;
                }
            }
        }

        if (isWhiteMove)
        {
            if (isCorrectCords(selectedLetter - 1, selectedIndex + 1))
            {
                short tempPiece = board.getPieceFrom(selectedLetter - 1, selectedIndex + 1);
                if (tempPiece == BLACK_PAWN)
                    result = true;
            }
            if (isCorrectCords(selectedLetter + 1, selectedIndex + 1))
            {
                short tempPiece = board.getPieceFrom(selectedLetter + 1, selectedIndex + 1);
                if (tempPiece == BLACK_PAWN)
                    result = true;
            }
        }
        else
        {
            if (isCorrectCords(selectedLetter - 1, selectedIndex - 1))
            {
                short tempPiece = board.getPieceFrom(selectedLetter - 1, selectedIndex - 1);
                if (tempPiece == WHITE_PAWN)
                    result = true;
            }
            if (isCorrectCords(selectedLetter + 1, selectedIndex - 1))
            {
                short tempPiece = board.getPieceFrom(selectedLetter + 1, selectedIndex - 1);
                if (tempPiece == WHITE_PAWN)
                    result = true;
            }
        }

        selectPiece(curSelectedLetter, curSelectedIndex);

        return result;
    }

    void drawPossibleMoves(sf::RenderWindow &window, short **possibleMoves)
    {
        sf::CircleShape dot;
        dot.setRadius(10.f);
        dot.setFillColor(sf::Color(100, 109, 64));

        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(65.f, 65.f));
        rect.setOutlineThickness(5.f);
        rect.setOutlineColor(sf::Color(100, 109, 64));
        rect.setFillColor(sf::Color::Transparent);

        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            if (board.getPieceFrom(possibleMoves[i][0] + 'a', possibleMoves[i][1]) == 0)
            {
                dot.setPosition(sf::Vector2f(27.5 + possibleMoves[i][0] * 75.f, 600 - 46 - possibleMoves[i][1] * 75.f));
                window.draw(dot);
            }
            else
            {
                rect.setPosition(sf::Vector2f(5 + possibleMoves[i][0] * 75.f, 600 + 5 - (possibleMoves[i][1] + 1) * 75.f));
                window.draw(rect);
            }
        }
    }

    bool isPossibleMove(char letter, short index, short **possibleMoves)
    {
        bool res = false;
        for (short i = 0; i < numberOfPossibleMoves; i++)
        {
            if ((possibleMoves[i][0] == letter - 'a') && (possibleMoves[i][1] == index))
            {
                res = true;
                break;
            }
        }
        return res;
    }

    void removeSelect()
    {
        selectedLetter = 0;
        selectedIndex = -1;
        numberOfPossibleMoves = 0;
    }

    short getSelectedPiece()
    {
        if (selectedLetter != 0 && selectedIndex != -1)
            return board.getPieceFrom(selectedLetter, selectedIndex);
        else
            return 0;
    }

    char getSelectedLetter()
    {
        return selectedLetter;
    }

    short getSelectedIndex()
    {
        return selectedIndex;
    }

    short getNumberOfPossibleCurrentKingMoves()
    {
        short curNumberOfPossibleMoves = numberOfPossibleMoves;
        char curSelectedLetter = selectedLetter;
        short curSelectedIndex = selectedIndex;

        short *kingCords = board.getKingCords(isWhiteMove);
        selectPiece(kingCords[0], kingCords[1]);

        getPossibleMoves();
        short result = numberOfPossibleMoves;

        numberOfPossibleMoves = curNumberOfPossibleMoves;
        selectPiece(curSelectedLetter, curSelectedIndex);

        return result;
    }

    bool isBlackMove()
    {
        return !isWhiteMove;
    }

    ChessBoard getBoard()
    {
        return board;
    }

private:
    ChessBoard board;
    bool isWhiteMove;
    char selectedLetter = 0;
    short selectedIndex = -1;
    short numberOfPossibleMoves = 0;
};
