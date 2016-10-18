#ifndef OBJECT_H
#define OBJECT_H
#include <QDebug>
#include <QRect>
#include "../../options.h"
#include <qmath.h>
#define Pi 3.14159265359



enum  Action{
    RIGHT = 1,
    LEFT,
    DOWN,
    UP,
    SHOT,
    NEXT_WEAPON,
    PREVIE_WEAPON
};

enum Position{
    TOP = 1,
    BOTTOM
};

enum Weapon{
    PISTOL = 1,
    UZI,
    ROCKET,
    WALL_WEAPON
};

enum TypeObject{
    MY_OBJECT =1,
    BULLET,
    WALL,
    BOT,
    KAMIKAZE,
    FAT_BOT
};


class Level{
public:
    Level(){}
    Level(int max_burn){
        max_burned = max_burn;
        time_to_burn = 40;
        for(int i = 0; i < max_burned; i++){
            if(i%2 == 1){
                //types_npc.push_back(BOT);
                types_npc.push_back(FAT_BOT);

            }
            else{
                types_npc.push_back(KAMIKAZE);
            }
        }

    }
    int max_burned;
    int time_to_burn;
    QVector<TypeObject>types_npc;

};


class Object
{
public:
    Object();
    virtual ~Object();

    void setX(const int x);
    void addX(const int x);

    void setY(const int y);
    void addY(const int y);

    void setWidth(const int width);
    void addWidth(const int width);

    void setHeight(const int height);
    void addHeight(const int height);

    void setAngle(const int angle);
    void addAngle(const int angle);

    void setStep(const int step);
    void addStep(const int step);

    void setHealth(const int health);
    void addHealth(const int health);

    void setIsLife(const bool);

    void setTypeObject(const TypeObject type);

    void setObjects(QVector<Object *> *const obj);

    int getX() const;
    int getY() const ;
    int getWidth() const;
    int getHeight() const ;
    int getAngle() const;
    int getStep() const;
    int getHealth() const;
    bool getIsLife() const;
    TypeObject getTypeObject() const;
    QVector<Object *> *getObjects()const ;

    bool operator ==(bool rhs);

    virtual void move() = 0;

private:
    int x_;
    int y_;
    int width_;
    int height_;
    int angle_;
    int step_;
    int health_;
    bool is_life_;
    TypeObject type_object_;
    QVector<Object *> *objects_;
};

bool intersectOnObjects(const Object *obj,QVector<Object *> *const objects);
bool intersectOnObjects(const int x_next, const int y_next, const Object *obj, QVector<Object *> *const objects);

#endif // OBJECT_H
