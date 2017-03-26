#ifndef UZIBEHAVIOR_H
#define UZIBEHAVIOR_H

#include "bulletbehavior.h"
#include "npcobject.h"

class UziBehavior : public BulletBehavior
{
public:
    UziBehavior();
    ~UziBehavior();
    virtual void hintInObject(Object *const npc = 0);
    virtual void hintInObject(Object *const npc = 0, QVector<Object *> *const objects = 0) {}
};

#endif // UZIBEHAVIOR_H
