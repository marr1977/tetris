#pragma once

#include <SFML/Graphics.hpp>

#include "TetrisBoard.h"

namespace Tetris
{

    class TetrisBoardDrawer
    {
    public:

        TetrisBoardDrawer(TetrisBoard& _board, sf::RenderWindow& _window);
        void Draw();
    private:

        TetrisBoard& board;
        sf::RenderWindow& window;
        sf::Font font;
    };

}