#ifndef BULLETBEHAVIOR_H
#define BULLETBEHAVIOR_H
//#include <QDebug>
#include "object.h"
//#include "bullet.h"

class NpcObject;

class BulletBehavior
{
public:
    BulletBehavior(Weapon w){
        weapon_ = w;
        count_ammunition_ = 0;
    }
    virtual ~BulletBehavior(){}
    void addAmmunition(const int ammunition){
        if(count_ammunition_ + ammunition >= 0){
            count_ammunition_ += ammunition;
        }
    }
    int getAmmunition() const {
        return count_ammunition_;
    }
    bool canShot() const {
        if(weapon_ == PISTOL){
            return true;
        }
        if(count_ammunition_ > 0){
            return true;
        }
        else{
            return false;
        }
    }
    virtual void hintInObject(Object *const npc) = 0;
    virtual void hintInObject(Object *const npc, QVector<Object *> *const objects) = 0;
    Weapon getWeapon() const{
        return weapon_;}

private:
    Weapon weapon_;
    int count_ammunition_;
};

#endif // BULLETBEHAVIOR_H

