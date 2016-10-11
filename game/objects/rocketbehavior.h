#ifndef ROCKETBEHAVIOR_H
#define ROCKETBEHAVIOR_H
#include "bulletbehavior.h"

class RocketBehavior : public BulletBehavior
{
public:
    RocketBehavior();
    ~RocketBehavior();
    virtual void hintInObject(Object *const npc){}
    virtual void hintInObject(Object *const npc, QVector<Object *> *const objects);
};

#endif // ROCKETBEHAVIOR_H
