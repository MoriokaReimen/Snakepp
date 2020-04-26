#pragma once

struct Position
{
    int x;
    int y;
};

inline bool operator==(const Position& lhs, const Position& rhs)
{
    if(lhs.x == rhs.x && lhs.y == rhs.y)
        return true;
    
    return false;
}