#ifndef LEVEL_H
#define LEVEL_H
#include "./objects/object.h"

class ValueXY{
public:
    ValueXY() :
        x(0), y(0){}
    ValueXY(int a, int b) :
        x(a), y(b){}
    int x;
    int y;
};

class Level{
public:
    Level() :
    max_burned(0),
    time_to_burn(0){}
    int max_burned;
    int time_to_burn;
    QVector<TypeObject>types_npc;
    QVector<ValueXY>walls;
};


#endif // LEVEL_H
