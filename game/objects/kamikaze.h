#ifndef KAMIKAZE_H
#define KAMIKAZE_H
#include "npcobject.h"


class Kamikaze : public NpcObject
{
public:
    Kamikaze();
    ~Kamikaze();
    virtual void initNpcObject(Object *const my,QVector<Object *> *const objects);
    virtual bool hintMyObject(const int x,const int y);
};

#endif // KAMIKAZE_H
