#ifndef BOT_H
#define BOT_H
#include "npcobject.h"


class Bot : public NpcObject
{
public:
    Bot();
    ~Bot();
    virtual void initNpcObject(Object *const my,QVector<Object *> *const objects);
    virtual bool hintMyObject(const int x,const int y);
};

#endif // BOT_H
