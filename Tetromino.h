#pragma once

#include <set>
#include <vector>
#include <utility>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace Tetris
{
    struct Point
    {
        int x;
        int y;

        bool operator== (const Point & other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator< (const Point & other) const
        {
            if (y < other.y )
                return true;
            
            if (y > other.y)
                return false;

            if (x < other.x)
                return true;

            if (x > other.x)
                return false;

            return false;
        }
    };

    std::ostream& operator<<(std::ostream& os, const std::set<Point>& points);
    std::ostream& operator<<(std::ostream& os, const Point& point);

    class Tetromino
    {
    public:
        void Translate(int deltaX, int deltaY) { x += deltaX; y += deltaY; };
        const sf::Color& GetColor() const { return color; }
        void GetPoints(std::set<Point>& actPoints) const 
        {
            actPoints.clear();
            const std::set<Point>& currentPoints = points.at(orientation % points.size());
            for (const auto& point : currentPoints)
            {
                actPoints.insert({point.x + x, point.y + y});
            }
        }

        void Rotate(bool clockwise)
        {
            if (clockwise)
                orientation++;
            else
                orientation--;
        }
    protected:
        Tetromino(const sf::Color& _color, int _x, int _y, const std::vector<std::set<Point>> & _points) : 
            color(_color), x(_x), y(_y), points(_points) {
        }
    protected:
        sf::Color color;

        int x;
        int y;
        std::vector<std::set<Point>> points;
        int orientation{0};
    };

    class ITetramino : public Tetromino
    {
    public:
        ITetramino(int x, int y) : Tetromino(sf::Color(61, 230, 230), x, y, {
            {{-2, 0}, {-1, 0}, {0, 0}, {1, 0}},
            {{0, -1}, {0, 0}, {0, 1}, {0, 2}},
            {{-2, 1}, {-1, 1}, {0, 1}, {1, 1}},
            {{-1, -1}, {-1, 0}, {-1, 1}, {-1, 2}}
        }) {};
    };

    class JTetramino : public Tetromino
    {
    public:
        JTetramino(int x, int y) : Tetromino(sf::Color(0, 40, 247), x, y, {
            {{-1, 0}, {-1, 1}, {0, 1}, {1,  1} },
            {{ 1, 0}, {0, 0},   {0, 1}, {0,  2} },
            {{-1,  1}, {0,  1}, {1, 1}, {1,  2} },
            {{-1,  2}, {0,  2}, {0, 1}, {0, 0} }
        }) {};
    };

    class LTetramino : public Tetromino
    {
    public:
        LTetramino(int x, int y) : Tetromino(sf::Color(255, 129, 43), x, y, {
            {{-1, 1}, {0, 1}, {1, 1}, {1, 0} },
            {{ 0, 0}, {0, 1}, {0, 2}, {1,  2} },
            {{-1, 2}, {-1, 1}, {0, 1}, {1, 1} },
            {{-1, 0}, {0,  0}, {0, 1}, {0, 2} }
        }) {};
    };

    class OTetramino : public Tetromino
    {
    public:
        OTetramino(int x, int y) : Tetromino(sf::Color(255, 253, 76), x, y, {
            {{-1, 0}, {-1, 1}, {0, 0}, {0, 1} },
            {{-1, 0}, {-1, 1}, {0, 0}, {0, 1} },
            {{-1, 0}, {-1, 1}, {0, 0}, {0, 1} },
            {{-1, 0}, {-1, 1}, {0, 0}, {0, 1} }
        }) {};
    };


    class STetramino : public Tetromino
    {
    public:
        STetramino(int x, int y) : Tetromino(sf::Color(0, 252, 73), x, y, {
            {{-1, 1}, {0, 1}, {0, 0}, {1, 0} },
            {{0, 0}, {0, 1}, {1, 1}, {1, 2} },
            {{-1, 2}, {0, 1}, {0, 2}, {1, 1} },
            {{-1, 0}, {0, 1}, {-1, 1}, {0, 2} }
        }) {};
    };

    class TTetramino : public Tetromino
    {
    public:
        TTetramino(int x, int y) : Tetromino(sf::Color(255, 47, 247), x, y, {
            {{-1, 1}, {0, 1}, {0, 0}, {1, 1} },
            {{0, 0},  {0, 1}, {1, 1}, {0, 2} },
            {{-1, 1}, {0, 1}, {1, 1}, {0, 2} },
            {{-1, 1}, {0, 1}, {0, 0}, {0, 2} }
        }) {};
    };

    class ZTetramino : public Tetromino
    {
    public:
        ZTetramino(int x, int y) : Tetromino(sf::Color(255, 28, 24), x, y, {
            {{-1, 0}, {0, 1}, {0, 0}, {1, 1} },
            {{0, 2},  {0, 1}, {1, 1}, {1, 0} },
            {{-1, 1}, {0, 1}, {0, 2}, {1, 2} },
            {{-1, 1}, {0, 1}, {-1, 2}, {0, 0} }
        }) {};
    };

}