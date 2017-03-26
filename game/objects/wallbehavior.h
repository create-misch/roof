#ifndef WALLBEHAVIOR_H
#define WALLBEHAVIOR_H

#include "bulletbehavior.h"


class WallBehavior : public BulletBehavior
{
public:
    WallBehavior();
    ~WallBehavior();
    virtual void hintInObject(Object *const npc = 0){}
    virtual void hintInObject(Object *const npc = 0, QVector<Object *> *const objects = 0) {}
};

#endif // WALLBEHAVIOR_H
