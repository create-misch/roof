#ifndef BULLET_H
#define BULLET_H
#include "object.h"
#include "bulletbehavior.h"
#include "pistolbehavior.h"
#include "uzibehavior.h"
#include "rocketbehavior.h"
#include "wallbehavior.h"
#include <QRect>



class Bullet : public Object
{
public:
    Bullet();
    ~Bullet();
    BulletBehavior *bulletBehavior;


    virtual void move();
    void initBullet(QVector<Object *> * const objects);
    void setBulletBehavior(BulletBehavior *behavior);
    void checkOnHint();
    Weapon getWeapon() const;
};

#endif // BULLET_H
