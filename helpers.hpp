#pragma once

#include "defines.hpp"

sf::Sprite convertNumberToPiece(short number, sf::Sprite *sprites)
{
    return sprites[number + 6];
}

short abs(short num)
{
    if (num > 0)
    {
        return num;
    }
    else
    {
        return -num;
    }
}

void printGame(sf::RenderWindow &window, ChessBoard board, sf::Sprite *sprites)
{
    sf::RectangleShape cell(sf::Vector2f(75.f, 75.f));

    for (short letter = 0; letter < 8; letter++)
    {
        for (short index = 7; index >= 0; index--)
        {
            if ((letter + index) % 2 != 0)
            {
                cell.setFillColor(sf::Color(240, 217, 181));
            }
            else
            {
                cell.setFillColor(sf::Color(181, 136, 99));
            }

            cell.setPosition(sf::Vector2f(letter * 75.f, (7 - index) * 75.f));
            window.draw(cell);
        }
    }

    for (short i = 7; i >= 0; i--)
    {
        for (char letter = 'a'; letter <= 'h'; letter++)
        {
            if (board.getPieceFrom(letter, i) != 0)
            {
                sf::Sprite piece = convertNumberToPiece(board.getPieceFrom(letter, i), sprites);
                piece.setPosition(sf::Vector2f((letter - 'a') * 75.f, (7 - i) * 75.f));
                window.draw(piece);
            }
        }
    }
}

short *getCoordinates(sf::Event event)
{
    short *result = new short[2];
    result[0] = event.mouseButton.x / 75 + 'a';
    result[1] = 7 - event.mouseButton.y / 75;
    return result;
}

bool clickInsideBoard(int x, int y)
{
    return (x >= 0 && x < 600) && (y >= 0 && y < 600);
}

bool clickInsideImproveField(int x, int y)
{
    return (x >= 1.5 * 75 && x < 6.5 * 75) && (y >= 225 && y < 375);
}

short getImprovedPiece(int x, int y)
{
    std::cout << x - 150 << '\n';
    switch ((x - 150) / 75)
    {
    case 0:
        return WHITE_QUEEN;

    case 1:
        return WHITE_ROOK;

    case 2:
        return WHITE_BISHOP;

    case 3:
        return WHITE_KNIGHT;

    case 4:
        return WHITE_KNIGHT;

    default:
        return 0;
    }
}

bool clickInsideNewGame(int x, int y)
{
    return (x >= 632 && x <= 865) && (y >= 257 && y <= 293);
}

bool clickInsideExit(int x, int y)
{
    return (x >= 632 && x <= 865) && (y >= 303 && y <= 339);
}