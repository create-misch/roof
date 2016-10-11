#ifndef UZIBEHAVIOR_H
#define UZIBEHAVIOR_H
#include "bulletbehavior.h"
#include "npcobject.h"

class UziBehavior : public BulletBehavior
{
public:
    UziBehavior();
    ~UziBehavior();
    virtual void hintInObject(Object *const npc);
    virtual void hintInObject(Object *const npc, QVector<Object *> *const objects) {}
};

#endif // UZIBEHAVIOR_H
