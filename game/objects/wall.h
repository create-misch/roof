#ifndef WALL_H
#define WALL_H
#include "object.h"


class Wall : public Object
{
public:
    Wall();
    ~Wall();
    void initWall(const int x, const int y);
    bool intersectOnObjects(const int x,const int y,QVector<Object *> *const npcs);
    virtual void move(){}
};

#endif // WALL_H
