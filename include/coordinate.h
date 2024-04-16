#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
    int x,y;    //x向下，y向右    //且从0开始
    int rN;     //开方后
public:
    Coordinate(int N0);
    Coordinate(int a,int b,int N0);

    int X();
    int Y();
    int N(); //返回rN的平方

    int retIndex();
    void setIndex(int a,int b);
    bool valid();

};

#endif // COORDINATE_H
