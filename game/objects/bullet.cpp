#include "bullet.h"

#include "pistolbehavior.h"
#include "uzibehavior.h"
#include "rocketbehavior.h"
#include "wallbehavior.h"

Bullet::Bullet() :
    Object()
{
    GameOptions *game_options = &Options::instance()->game_option;
    bulletBehavior = 0;
    setHeight(game_options->getBulletHeight());
    setWidth(game_options->getBulletWidth());
    setStep(game_options->getBulletStep());
    setIsLife(true);
    setTypeObject(BULLET);
}

Bullet::~Bullet()
{

}

void Bullet::move()
{    
    int x , y;
    switch(getAngle()){
    case 0:
        x = getX() + getStep();
        y = getY();
        break;
    case 90:
        y = getY() + getStep();
        x = getX();
        break;
    case 180:
        x = getX() - getStep();
        y = getY();
        break;
    case 270:
        y = getY() -  getStep();
        x = getX();
        break;

    default:
        x = getX();
        y = getY();
        break;

    }

    if(x > 0 && x < Options::instance()->app_option.getGameSpaceWidth()
            && y > 0  && y < Options::instance()->app_option.getGameSpaceHeight()){ //ограничение на
        setX(x);
        setY(y);
    }
    if((x <= 0) || (x >= Options::instance()->app_option.getGameSpaceWidth())
            || (y <= 0)  || (y >= Options::instance()->app_option.getGameSpaceHeight())){
        setIsLife(false);
    }
}

void Bullet::initBullet(QVector<Object *> * const objects)
{
    setObjects(objects);
}

void Bullet::setBulletBehavior(BulletBehavior *behavior)
{
    bulletBehavior = behavior;
}

void Bullet::checkOnHint()
{
    if(getIsLife() == false){
        return;
    }
    if(bulletBehavior == 0){
        return;
    }

    for(QVector<Object *>::iterator it = getObjects()->begin(); it != getObjects()->end(); it++){
        if(this != (*it)){
            if((*it)->getIsLife() == true){
                QRect bullet_rect(getX(), getY(), getWidth(), getHeight());
                QRect npc_rect((*it)->getX(), (*it)->getY(), (*it)->getWidth(), (*it)->getHeight());
                if(bullet_rect.intersects(npc_rect)){
                    if(bulletBehavior->getWeapon() == ROCKET){
                        bulletBehavior->hintInObject((*it), getObjects());
                    }
                    else{
                        bulletBehavior->hintInObject((*it));
                    }
                    setIsLife(false);
                }
            }
        }
    }

}

Weapon Bullet::getWeapon() const
{
    if(bulletBehavior != 0){
        return bulletBehavior->getWeapon();
    }
}
