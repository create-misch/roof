#ifndef FATBOT_H
#define FATBOT_H

#include "npcobject.h"


class FatBot : public NpcObject
{
public:
    FatBot();
    ~FatBot();
    virtual void initNpcObject(Object *const my,QVector<Object *> *const objects);
    virtual bool hintMyObject(const int x,const int y);
};

#endif // FATBOT_H
