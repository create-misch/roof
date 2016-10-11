#ifndef NPCOBJECT_H
#define NPCOBJECT_H

#include "object.h"

class NpcObject : public Object
{
public:
    NpcObject();
    virtual ~NpcObject();
    bool initPosition(const Position position);
    void setMyObject(Object *const my_object);
    Object *getMyObject() const;
    virtual void move();
    virtual void initNpcObject(Object *const my,QVector<Object *> *const objects) = 0;
    virtual bool hintMyObject(const int x,const int y) = 0;

private:
    bool canMove(const int x,const int y);
    bool intersectOnObjects(const int x,const int y,QVector<Object *> *const npcs);
    void calculateAngle();
    bool operator ==(Object *rhs);


    Object *my_object_;
};

#endif // NPCOBJECT_H
