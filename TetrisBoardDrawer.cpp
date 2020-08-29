#include "TetrisBoardDrawer.h"

#include <iostream>

namespace Tetris
{
    

    TetrisBoardDrawer::TetrisBoardDrawer(TetrisBoard& _board, sf::RenderWindow& _window) : board(_board), window(_window)
    {
        if (!font.loadFromFile("arial.ttf"))
            std::cerr << "Error loading font" << std::endl;
    }

    void TetrisBoardDrawer::Draw()
    {
        float boxSize = 25;

        float width = boxSize * board.GetWidth();
        float height = boxSize * board.GetHeight();

        float startX = (window.getSize().x - width) / 2;
        float startY = (window.getSize().y - height) / 2;

        float lineSize = 1.0f;

        sf::Color gridColor(128, 128, 128);

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString(std::string("Score: ") + std::to_string(board.GetScore()));
        scoreText.setPosition(5, 5);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(gridColor);
        window.draw(scoreText);

        sf::Text levelText;
        levelText.setFont(font);
        levelText.setString(std::string("Level: ") + std::to_string(board.GetLevel()));
        levelText.setPosition(scoreText.getPosition().x, scoreText.getPosition().y + scoreText.getCharacterSize() + 5);
        levelText.setCharacterSize(24);
        levelText.setFillColor(gridColor);
        window.draw(levelText);

        if (!board.IsActive())
        {
            sf::Text text;
            text.setFont(font);
            text.setString("Press enter to start");
            text.setPosition(190, 55);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Yellow);
            window.draw(text);

            if (board.IsGameOver())
            {
                sf::Text text;
                text.setFont(font);
                text.setString("Game over! Good job!");
                text.setPosition(180, 100);
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Red);
                window.draw(text);
            }
        }
        else
        {
            if (board.GetNextTetromino())
            {
                std::set<Point> points;
                board.GetNextTetromino()->GetPoints(points);

                float nextY = startY + (board.GetHeight() / 3) * boxSize;
                float nextX = startX + (board.GetWidth() - 3) * boxSize + 10;

                sf::Text text;
                text.setFont(font);
                text.setString("Next");
                text.setCharacterSize(16);
                text.setPosition(nextX + 110, nextY - text.getCharacterSize() - 15);
                text.setFillColor(gridColor);
                window.draw(text);

                for (const Point& pt : points)
                {
                    if (pt.y < 0) {
                        continue;
                    }
                    float topX = nextX + pt.x * boxSize;
                    float topY = nextY + pt.y * boxSize;
        
                    sf::RectangleShape box({boxSize, boxSize});
                    box.setFillColor(board.GetNextTetromino()->GetColor());
                    box.setPosition(topX, topY);
                    window.draw(box);
                }

            }
        }
        

        if (board.GetMovingTetromino())
        {
            std::set<Point> points;
            board.GetMovingTetromino()->GetPoints(points);

            for (const Point& pt : points)
            {
                if (pt.y < 0) {
                    continue;
                }
                float topX = startX + pt.x * boxSize;
                float topY = startY + pt.y * boxSize;
    
                sf::RectangleShape box({boxSize, boxSize});
                box.setFillColor(board.GetMovingTetromino()->GetColor());
                box.setPosition(topX, topY);
                window.draw(box);
            }

        }

        for (const auto& pair : board.GetPoints())
        {
            if (pair.first.y < 0) {
                continue;
            }
            float topX = startX + pair.first.x * boxSize;
            float topY = startY + pair.first.y * boxSize;

            sf::RectangleShape box({boxSize, boxSize});
            box.setFillColor(pair.second);
            box.setPosition(topX, topY);
            window.draw(box);
        }

         // Draw vertical lines
        for (int i = 0; i <= board.GetWidth(); i++)
        {
            sf::RectangleShape line({lineSize, height});
            line.setFillColor(gridColor);
            line.setPosition(startX + i * boxSize, startY);
            window.draw(line);
        }

        // Draw horizontal lines
        for (int i = 0; i <= board.GetHeight(); i++)
        {
            sf::RectangleShape line({width, lineSize});
            line.setFillColor(gridColor);
            line.setPosition(startX, startY + i * boxSize);
            window.draw(line);
        }

        // Print highscores
        size_t pos = 1;
        float highScoreX = 40;
        float highScoreY = startY;
        float textHeight = 12;
        float scoreSpacing = 20;
        float textSpacing = 5;
        float titleTextHeight = 16;
        sf::Color highScoreColor(24, 220, 24);

        {
            sf::Text text;
            text.setFont(font);
            text.setString("Highscores");
            text.setPosition(highScoreX, highScoreY);
            text.setCharacterSize(titleTextHeight);
            text.setFillColor(highScoreColor);
            window.draw(text);
        }

        for (HighScores::Score score : board.GetHighScores())
        {
            float scoreY = highScoreY + titleTextHeight + scoreSpacing + 
                (textHeight * 2 + textSpacing + scoreSpacing) * (pos - 1);
            float nameY = scoreY + textSpacing + textHeight;

            {
                sf::Text text;
                text.setFont(font);
                text.setString(score.name);
                text.setPosition(highScoreX, nameY);
                text.setCharacterSize(textHeight);
                text.setFillColor(highScoreColor);
                window.draw(text);
            }

            {
                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(score.score));
                text.setPosition(highScoreX, scoreY);
                text.setCharacterSize(textHeight);
                text.setFillColor(highScoreColor);
                window.draw(text);
            }

            pos++;
        }
    }
}