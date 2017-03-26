#ifndef BULLET_H
#define BULLET_H

#include "object.h"

#include <QRect>

class BulletBehavior;
class UziBehavior;
class RocketBehavior;
class WallBehavior;

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
