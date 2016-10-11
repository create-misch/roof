#include "myobject.h"

MyObject::MyObject(QObject *parent) : QObject(parent), Object()
{

}

MyObject::~MyObject()
{
    QVector<BulletBehavior *>::iterator it;
    for(it = weapons.begin(); it != weapons.end(); it++){
        delete *it;
    }
}

void MyObject::initMyObject(QVector<Object *> * const obj)
{
    if(obj != 0){
        setObjects(obj);
    }
    setTypeObject(MY_OBJECT);
    setIsLife(true);
    setX(300);
    setY(200);
    setHealth(Options::instance()->game_option.getMyHealth());
    setHeight(Options::instance()->game_option.getMyObjectHeight());
    setWidth(Options::instance()->game_option.getMyObjectWidth());
    setStep(Options::instance()->game_option.getMyStep());
    setAngle(270);
    initWeapons();
}

void MyObject::initWeapons()
{
    if(weapons.isEmpty() == false){
        weapons.clear();
    }
    weapons.push_back(new PistolBehavior);
    weapons.last()->addAmmunition(100);
    weapons.push_back(new UziBehavior);
    weapons.last()->addAmmunition(100);
    weapons.push_back(new RocketBehavior);
    weapons.last()->addAmmunition(100);
    weapons.push_back(new WallBehavior);
    weapons.last()->addAmmunition(10);
    my_weapon = weapons.begin();
}

void MyObject::nextWeapon()
{
    if(my_weapon == weapons.end() - 1){
        return;
    }
    my_weapon++;
}

void MyObject::previeWeapon()
{
    if(my_weapon  == weapons.begin()){
        return;
    }
    my_weapon--;
}

Weapon MyObject::getWeapon() const
{
    if(my_weapon != 0){
        BulletBehavior *bull = *my_weapon;
        return bull->getWeapon();
    }
}

void MyObject::move()
{
    int x , y;
    x = static_cast<int>(getX() + getStep()*(int)cos(getAngle()*Pi/180));
    y = static_cast<int>(getY() + getStep()*(int)sin(getAngle()*Pi/180));
    if(x > 0 && x < Options::instance()->app_option.getGameSpaceWidth() - getWidth()
            && y > 0  && y < Options::instance()->app_option.getGameSpaceHeight() - getHeight()){ //ограничение на
        if(canMove(x, y) == true){
            setX(x);
            setY(y);
        }
    }

}

bool MyObject::canMove(const int x,const int y)
{
    if(intersectOnObjects(x, y, getObjects()) == true){
        return false;
    }
    return true;
}

bool MyObject::intersectOnObjects(const int x,const int y,QVector<Object *> *const objects)
{
    QRect my_rect(x, y, getWidth(), getHeight());

    for(QVector<Object *>::const_iterator it = objects->begin(); it != objects->end(); it++){
        Object *obj = *it;
        QRect npc_rect(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight());
        if(my_rect.intersects(npc_rect)){
            return true;
        }
    }
    return false;
}

void MyObject::shot()
{
    BulletBehavior *weapon = *my_weapon;
    if(weapon->canShot() == false){
        return;
    }
    if(weapon->getWeapon() == WALL_WEAPON){
        int x , y;
        x = static_cast<int>(getX() + getWidth()*(int)cos(getAngle()*Pi/180));
        y = static_cast<int>(getY() + getHeight()*(int)sin(getAngle()*Pi/180));
        if(x > 0 && x < Options::instance()->app_option.getGameSpaceWidth() - getWidth()
                && y > 0  && y < Options::instance()->app_option.getGameSpaceHeight() - getHeight()){
            Wall *wall = new Wall;
            if(wall->intersectOnObjects(x, y, getObjects()) == false){
                wall->initWall(x, y);
                weapon->addAmmunition(-1);
                getObjects()->push_back(wall);
            }
            else{
                delete wall;
            }
            return;
        }
    }
    Bullet *bullet = new Bullet;
    bullet->setObjects(getObjects());
    bullet->setBulletBehavior(*my_weapon);
    bullet->setAngle(getAngle());
    bullet->setX(getX() + getWidth()/2);
    bullet->setY(getY() + getHeight()/2);
    weapon->addAmmunition(-1);
    getObjects()->push_back(bullet);
}

void MyObject::getAction_slot(Action action)
{
    switch (action) {
    case UP:
        setAngle(270);
        move();
        break;
    case RIGHT:
        setAngle(0);
        move();
        break;
    case DOWN:
        setAngle(90);
        move();
        break;
    case LEFT:
        setAngle(180);
        move();
        break;
    case SHOT:
        shot();
        break;
    case NEXT_WEAPON:
        nextWeapon();
        break;
    case PREVIE_WEAPON:
        previeWeapon();
        break;
    default:
        break;
    }
}
