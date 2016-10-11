#ifndef WALLBEHAVIOR_H
#define WALLBEHAVIOR_H
#include "bulletbehavior.h"


class WallBehavior : public BulletBehavior
{
public:
    WallBehavior();
    ~WallBehavior();
    virtual void hintInObject(Object *const npc){}
    virtual void hintInObject(Object *const npc, QVector<Object *> *const objects) {}
};

#endif // WALLBEHAVIOR_H
