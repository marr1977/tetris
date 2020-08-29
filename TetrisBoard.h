#pragma once

#include "Tetromino.h"
#include <memory>
#include <vector>
#include <chrono>
#include <random>

namespace Tetris
{
    typedef std::unique_ptr<Tetromino> TetrominoPtr;

    class TetrisBoard
    {
    public:
        TetrisBoard();

        void Start();
        void Tick();

        const TetrominoPtr& GetMovingTetromino() const { return movingTetramino; }
        const std::map<Point, sf::Color>& GetPoints() const { return stationaryPoints; }

        const int GetHeight() const { return height; }
        const int GetWidth() const { return width; }
        int GetScore() const { return score; }
        int GetLevel() const { return level; }
        void MoveLeft();
        void MoveRight();
        void MoveDown();
        void Rotate(bool clockwise);
        bool IsActive() const { return active; }
        bool IsGameOver() const { return !active && stationaryPoints.size() > 0; }
    private:
        bool IsTimeToTick();
        void MoveActiveTetramino(int deltax, int deltay);
        void MoveTetramino();
        void GenerateTetramino();
        Tetromino* GetRandomTetramino();
        bool InvalidPointSet(const std::set<Point>& points) const;
        void RemoveFilledLines();
    private:
        TetrominoPtr movingTetramino;
        std::map<Point, sf::Color> stationaryPoints;

        bool active{false};

        int width{10};
        int height{20};

        std::chrono::steady_clock::time_point lastTick;
        
        static constexpr long INITIAL_MILLISECONDS_BETWEEN_TICK{200};

        long millisecondsBetweenTick;

        std::random_device rd; 
        std::mt19937 gen;
        std::uniform_int_distribution<> distrib;

        int score{0};
        int level{0};
        int totalLinesRemoved;
    };



}