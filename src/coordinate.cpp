#include "coordinate.h"


Coordinate::Coordinate(int N0)
{
    rN = N0;
    x = y = rN - 1;
}

Coordinate::Coordinate(int a, int b, int N0)
{
    x = a;
    y = b;
    rN = N0;
}

int Coordinate::X()
{
    return x;
}

int Coordinate::Y()
{
    return y;
}

int Coordinate::N()
{
    return rN*rN;
}

int Coordinate::retIndex()
{
    return (rN*x+y);
}

void Coordinate::setIndex(int a, int b)
{
    x = a;
    y = b;
}

bool Coordinate::valid()
{
    if(x<0||y<0||x>=rN||y>=rN)
           return false;
       return true;
}
