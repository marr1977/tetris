#include "Tetromino.h"

namespace Tetris
{
    std::ostream& operator<<(std::ostream& os, const std::set<Point>& points)
    {
        os << "[";
        bool first = true;
        for (const auto& pt : points)
        {
            if (!first)
                os << ", ";
                
            os << pt;
            first = false;
        }
        os << "]";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Point& point)
    {
        os << "[" << point.x << ", " << point.y << "]";
        return os;
    }

}