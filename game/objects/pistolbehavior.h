#ifndef PISTOLBEHAVIOR_H
#define PISTOLBEHAVIOR_H
#include "bulletbehavior.h"

class PistolBehavior : public BulletBehavior
{
public:
    PistolBehavior();
    ~PistolBehavior();
    virtual void hintInObject(Object *const npc);
    virtual void hintInObject(Object *const npc, QVector<Object *> *const objects) {}

};

#endif // PISTOLBEHAVIOR_H
