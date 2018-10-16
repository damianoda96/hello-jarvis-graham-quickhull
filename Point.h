#ifndef POINT_H
#define POINT_H

//This is a simple struct that stores the coordinate pairs for the algorithms

struct Point
{
    int x, y;
    
    Point()
    {
    }
    
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    
    public:
    
    void print()
    {
        std::cout << "(" << x << "," << y << ")" << std::endl;
    }
    
};

#endif
