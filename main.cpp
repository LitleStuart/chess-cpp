#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ChessArbiter.hpp"
#include "helpers.hpp"

int main()
{
    std::string path = "/Users/ivan/Desktop/Developing/Cpp/chess-cpp/";

    // textures must be alive the whole program life
    sf::Texture whiteKingTex;
    sf::Texture whiteQueenTex;
    sf::Texture whiteBishopTex;
    sf::Texture whiteKnightTex;
    sf::Texture whiteRookTex;
    sf::Texture whitePawnTex;
    sf::Texture blackKingTex;
    sf::Texture blackQueenTex;
    sf::Texture blackBishopTex;
    sf::Texture blackKnightTex;
    sf::Texture blackRookTex;
    sf::Texture blackPawnTex;

    whiteKingTex.loadFromFile(path + "sprites/whiteKing.png");
    whiteQueenTex.loadFromFile(path + "sprites/whiteQueen.png");
    whiteBishopTex.loadFromFile(path + "sprites/whiteBishop.png");
    whiteKnightTex.loadFromFile(path + "sprites/whiteKnight.png");
    whiteRookTex.loadFromFile(path + "sprites/whiteRook.png");
    whitePawnTex.loadFromFile(path + "sprites/whitePawn.png");
    blackKingTex.loadFromFile(path + "sprites/blackKing.png");
    blackQueenTex.loadFromFile(path + "sprites/blackQueen.png");
    blackBishopTex.loadFromFile(path + "sprites/blackBishop.png");
    blackKnightTex.loadFromFile(path + "sprites/blackKnight.png");
    blackRookTex.loadFromFile(path + "sprites/blackRook.png");
    blackPawnTex.loadFromFile(path + "sprites/blackPawn.png");

    sf::Sprite whiteKing;
    sf::Sprite whiteQueen;
    sf::Sprite whiteBishop;
    sf::Sprite whiteKnight;
    sf::Sprite whiteRook;
    sf::Sprite whitePawn;
    sf::Sprite blackKing;
    sf::Sprite blackQueen;
    sf::Sprite blackBishop;
    sf::Sprite blackKnight;
    sf::Sprite blackRook;
    sf::Sprite blackPawn;

    whiteKing.setTexture(whiteKingTex);
    whiteQueen.setTexture(whiteQueenTex);
    whiteBishop.setTexture(whiteBishopTex);
    whiteKnight.setTexture(whiteKnightTex);
    whiteRook.setTexture(whiteRookTex);
    whitePawn.setTexture(whitePawnTex);
    blackKing.setTexture(blackKingTex);
    blackQueen.setTexture(blackQueenTex);
    blackBishop.setTexture(blackBishopTex);
    blackKnight.setTexture(blackKnightTex);
    blackRook.setTexture(blackRookTex);
    blackPawn.setTexture(blackPawnTex);

    sf::Sprite *sprites = new sf::Sprite[13];
    sprites[WHITE_KING + 6] = whiteKing;
    sprites[WHITE_QUEEN + 6] = whiteQueen;
    sprites[WHITE_BISHOP + 6] = whiteBishop;
    sprites[WHITE_KNIGHT + 6] = whiteKnight;
    sprites[WHITE_ROOK + 6] = whiteRook;
    sprites[WHITE_PAWN + 6] = whitePawn;
    sprites[BLACK_KING + 6] = blackKing;
    sprites[BLACK_QUEEN + 6] = blackQueen;
    sprites[BLACK_BISHOP + 6] = blackBishop;
    sprites[BLACK_KNIGHT + 6] = blackKnight;
    sprites[BLACK_ROOK + 6] = blackRook;
    sprites[BLACK_PAWN + 6] = blackPawn;

    ChessArbiter arb = ChessArbiter();
    arb.startGame();

    sf::RenderWindow window;
    window.create(sf::VideoMode(900, 600), "Chess", sf::Style::Titlebar | sf::Style::Close);

    sf::Texture menuTex;
    menuTex.loadFromFile(path + "sprites/menu.png");
    sf::Sprite menu;
    menu.setTexture(menuTex);
    menu.setPosition(sf::Vector2f(600, 0));

    sf::Font font;
    font.loadFromFile(path + "fonts/fifaks.ttf");
    sf::Text whichTurn;
    whichTurn.setFont(font);
    whichTurn.setCharacterSize(36);
    whichTurn.setFillColor(sf::Color::White);
    whichTurn.setPosition(sf::Vector2f(660, 100));

    sf::RectangleShape improveField(sf::Vector2f(5 * 75.f, 2 * 75.f));
    improveField.setFillColor(sf::Color::Black);
    improveField.setPosition(sf::Vector2f(1.5 * 75.f, 3 * 75.f));

    short **possibleMoves;
    short *cords;
    short selectedPiece = 0;
    bool isCheckMate = false;
    bool isOpenImproveField = false;

    while (window.isOpen())
    {
        std::string improve = isOpenImproveField ? "  Select  \nYour piece" : "";
        std::string check = arb.isCheck() ? "  Check!  \n" : "";
        std::string color = arb.isBlackMove() ? "Black move" : "White move";

        if (isOpenImproveField)
            whichTurn.setString(improve);
        else if (isCheckMate)
            whichTurn.setString("Checkmate!");
        else
            whichTurn.setString(check + color);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (clickInsideBoard(event.mouseButton.x, event.mouseButton.y) && !isCheckMate)
                {
                    if (isOpenImproveField)
                    {
                        if (clickInsideImproveField(event.mouseButton.x, event.mouseButton.y))
                        {
                            short improvedPiece = arb.isBlackMove()
                                                      ? getImprovedPiece(event.mouseButton.x, event.mouseButton.y)
                                                      : -getImprovedPiece(event.mouseButton.x, event.mouseButton.y);
                            arb.improve(cords[0], cords[1], improvedPiece);
                            isOpenImproveField = false;
                        }
                    }
                    else
                    {
                        cords = getCoordinates(event);
                        if (arb.isPossibleMove(cords[0], cords[1], possibleMoves))
                        {
                            arb.moveTo(cords[0], cords[1]);
                            if (cords[1] == (arb.isBlackMove() ? 7 : 0) && abs(arb.getBoard().getPieceFrom(cords[0], cords[1])) == WHITE_PAWN)
                            {
                                isOpenImproveField = true;
                            }
                            isCheckMate = arb.isCheckMate();
                        }
                        else if (arb.selectPiece(cords[0], cords[1]))
                        {
                            possibleMoves = arb.getPossibleMoves();
                        }
                        else
                            arb.removeSelect();
                    }
                }
                else if (clickInsideNewGame(event.mouseButton.x, event.mouseButton.y))
                {
                    arb.startGame();
                    isCheckMate = false;
                }
                else if (clickInsideExit(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(menu);
        window.draw(whichTurn);
        printGame(window, arb.getBoard(), sprites);
        if (isOpenImproveField)
        {
            whiteQueen.setPosition(sf::Vector2f(2 * 75.f, 3.5 * 75.f));
            whiteRook.setPosition(sf::Vector2f(3 * 75.f, 3.5 * 75.f));
            whiteBishop.setPosition(sf::Vector2f(4 * 75.f, 3.5 * 75.f));
            whiteKnight.setPosition(sf::Vector2f(5 * 75.f, 3.5 * 75.f));
            window.draw(improveField);
            window.draw(whiteQueen);
            window.draw(whiteRook);
            window.draw(whiteBishop);
            window.draw(whiteKnight);
        }

        arb.drawPossibleMoves(window, possibleMoves);

        window.display();
    }
}