#include <SFML/Graphics.hpp>

#include "TetrisBoard.h"
#include "TetrisBoardDrawer.h"

#include <iostream>

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "Tetris");
    window.setFramerateLimit(60); // Lowers cpu usage drastically

    std::string playerName;
    if (argc > 1)
        playerName = argv[1];

    const char* home = getenv("HOME");
    std::string highScoreFile = std::string(home) + std::string("/highscores.txt");

    Tetris::TetrisBoard board(playerName, highScoreFile);
    Tetris::TetrisBoardDrawer boardDrawer(board, window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type ==  sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                    board.MoveLeft();
                else if (event.key.code == sf::Keyboard::Right)
                    board.MoveRight();
                else if (event.key.code == sf::Keyboard::Space)
                    board.MoveDown();
                else if (event.key.code == sf::Keyboard::Up)
                    board.Rotate(true);
                else if (event.key.code == sf::Keyboard::Down)
                    board.Rotate(false);
                else if (event.key.code == sf::Keyboard::Enter)
                    board.Start();  

            }
           

            
        }

        board.Tick();

        window.clear();
        boardDrawer.Draw();
        window.display();
    }

    return 0;
}