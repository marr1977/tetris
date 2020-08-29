#include "TetrisBoard.h"
#include <iostream>

namespace Tetris
{


    
    TetrisBoard::TetrisBoard() : gen(rd()), distrib(1,7)
    {

    }

    void TetrisBoard::Start()
    {
        if (active)
            return;

        millisecondsBetweenTick = INITIAL_MILLISECONDS_BETWEEN_TICK;
        lastTick = std::chrono::steady_clock::now();
        active = true;
        score = 0;
        level = 1;
        totalLinesRemoved = 0;
        stationaryPoints.clear();
        std::cout << "Start" << std::endl;
    }

    void TetrisBoard::Tick()
    {
        if (!IsTimeToTick())
            return;

        if (movingTetramino)
        {
            MoveActiveTetramino(0, 1);
        }
        else
        {
            GenerateTetramino();
        }
    }

    bool TetrisBoard::IsTimeToTick()
    {
        if (!active)
            return false;

        auto now = std::chrono::steady_clock::now();

        long millisecondsSinceLastTick = std::chrono::duration_cast<std::chrono::milliseconds> (now - lastTick).count();

        if (millisecondsSinceLastTick < millisecondsBetweenTick)
            return false;

        lastTick = now;
        return true;
        
    }

    bool TetrisBoard::InvalidPointSet(const std::set<Point>& points) const
    {
        // Check if any points have reached the bottom
        for (const auto& point : points)
        {
            if (point.y >= height) 
                return true;

            if (point.x < 0 || point.x >= width)
                return true;
        }

        // Check if any point is already occupied
        for (const auto& point : points)
        {
            if (stationaryPoints.find(point) != stationaryPoints.end())
                return true;
        }

        return false;
    }

    void TetrisBoard::MoveLeft()
    {
        MoveActiveTetramino(-1, 0);
    }
    
    void TetrisBoard::MoveRight()
    {
        MoveActiveTetramino(1, 0);
    }

    void TetrisBoard::MoveDown()
    {
        MoveActiveTetramino(0, 1);
    }
    

    void TetrisBoard::Rotate(bool clockwise)
    {
        if (!movingTetramino)
            return;

        movingTetramino->Rotate(clockwise);

        // Check out-of-bounds et.c.
        std::set<Point> points;
        movingTetramino->GetPoints(points);
        
        if (InvalidPointSet(points)) {
            movingTetramino->Rotate(!clockwise);
        }
    }

    
    void TetrisBoard::MoveActiveTetramino(int deltax, int deltay)
    {
        if (!active)
            return;

        if (!movingTetramino)
            return;

        movingTetramino->Translate(deltax, deltay);
        
        std::set<Point> points;
        movingTetramino->GetPoints(points);
        
        if (InvalidPointSet(points))
        {
            // Move it back
            movingTetramino->Translate(-deltax, -deltay);

            // If we are trying to go down and failed, we stop it
            if (deltay > 0) {

                movingTetramino->GetPoints(points);
                for (const auto& pt : points)
                    stationaryPoints[pt] = movingTetramino->GetColor();

                movingTetramino.reset();
                RemoveFilledLines();
                GenerateTetramino();
            }
        } 
            
    }

    void TetrisBoard::RemoveFilledLines()
    {
        std::cout << std::endl;

        int linesRemoved = 0;
        while (true)
        {
            int filledRow = -1;

            for (int row = height -1; row >= 0; row--)
            {
                bool allColumnsOccupied = true;
                for (int col = 0; col < width; ++col)
                {
                    if (stationaryPoints.find({col, row}) == stationaryPoints.end())
                    {
                        allColumnsOccupied = false;
                        break;
                    }
                }

                if (allColumnsOccupied)
                {
                    filledRow = row;
                    break;
                }
            }

            if (filledRow < 0)
                break;

            std::cout << "Removing line " << filledRow << std::endl;

            ++linesRemoved;

            // Remove all points on filledRow  
            for (int col = 0; col < width; ++col)
                stationaryPoints.erase({col, filledRow});

            if (filledRow > 0)
            {
                // Move cells above this row down one row
                for (int row = filledRow - 1; row >= 0; --row)
                {
                    for (int col = 0; col < width; ++col)
                    {
                        auto iterator = stationaryPoints.find({col, row});
                        if (iterator != stationaryPoints.end())
                        {
                            sf::Color color = iterator->second;
                            stationaryPoints.erase(iterator);
                            stationaryPoints.insert(std::make_pair(Point{col, row + 1}, color));
                        }
                    }
                }
            }
        }

        if (linesRemoved == 1)
            score += 40 * level;
        else if (linesRemoved == 2)
            score += 100 * level;
        else if (linesRemoved == 3)
            score += 300 * level;
        else if (linesRemoved == 4)
            score += 1200 * level;

        if (linesRemoved > 0)
        {
            totalLinesRemoved += linesRemoved;
            if (totalLinesRemoved % 10 == 0)
            {
                level++;
                millisecondsBetweenTick *= 0.9;
            }
        }
    }

    Tetromino* TetrisBoard::GetRandomTetramino()
    {
        switch (distrib(gen))
        {
            case 1: return new JTetramino(width / 2, 0);
            case 2: return new ITetramino(width / 2, 0);
            case 3: return new LTetramino(width / 2, 0);
            case 4: return new OTetramino(width / 2, 0);
            case 5: return new STetramino(width / 2, 0);
            case 6: return new TTetramino(width / 2, 0);
            case 7: return new ZTetramino(width / 2, 0);
            default: return nullptr;
        }
    }

    void TetrisBoard::GenerateTetramino()
    {
        if (!nextTetramino)
            nextTetramino = std::unique_ptr<Tetromino>(GetRandomTetramino());

        std::set<Point> points;
        nextTetramino->GetPoints(points);

        if (InvalidPointSet(points))
        {
            std::cout << "Game over!" << std::endl;
            active = false;
        }
        else
        {
            movingTetramino = std::move(nextTetramino);
        }

        std::cout << "Generated" << std::endl;       
        nextTetramino = std::unique_ptr<Tetromino>(GetRandomTetramino());
    }

}