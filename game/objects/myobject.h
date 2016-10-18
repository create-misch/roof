#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

#include "object.h"
#include "bullet.h"
#include "wall.h"


class MyObject : public QObject , public Object
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = 0);
    ~MyObject();
    void initMyObject(QVector<Object *> * const obj);
    void initWeapons();
    void nextWeapon();
    void previeWeapon();
    Weapon getWeapon() const;
    virtual void move();
    bool canMove(const int x,const int y);
    void shot();

    QVector<BulletBehavior *>weapons;
    QVector<BulletBehavior *>::iterator my_weapon;


signals:

public slots:
    void getAction_slot(const Action action);
};

#endif // MYOBJECT_H
