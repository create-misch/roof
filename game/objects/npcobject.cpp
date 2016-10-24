#include "npcobject.h"

NpcObject::NpcObject():
    Object()
{
    my_object_ = 0;
}

NpcObject::~NpcObject()
{

}

bool NpcObject::initPosition(const Position position)
{
    setHeight(Options::instance()->game_option.getNpcHeight());
    setWidth(Options::instance()->game_option.getNpcWidth());


    switch(position){
    case TOP:
        setX(Options::instance()->app_option.getGameSpaceWidth()/2 - getWidth()/2);
        setY(0);
        break;

    case BOTTOM:
        setX(Options::instance()->app_option.getGameSpaceWidth()/2 - getWidth()/2);
        setY(Options::instance()->app_option.getGameSpaceHeight() - getHeight());
        break;

    default:
        break;
    }
    if(intersectOnObjects(this, getObjects()) == true){
        return false;
    }
    else{
        return true;
    }
}

void NpcObject::setMyObject(Object *const my_object)
{
    if(my_object == 0){
        return;
    }
    my_object_ = my_object;
}

Object *NpcObject::getMyObject() const
{
    return my_object_;
}

void NpcObject::move()
{
    calculateAngle();
    int x , y;
    x = static_cast<int>(getX() + getStep()*cos(getAngle()*Pi/180));
    y = static_cast<int>(getY() + getStep()*sin(getAngle()*Pi/180));
    if(x > 0 && x < Options::instance()->app_option.getGameSpaceWidth() - getWidth()
            && y > 0  && y < Options::instance()->app_option.getGameSpaceHeight() - getHeight()){ //ограничение на
        if(hintMyObject(x, y) == true){
            return;
        }
        if(canMove(x , y) == true){
            setX(x);
            setY(y);
        }
    }
}

bool NpcObject::canMove(const int x,const int y)
{
    if(intersectOnObjects(x, y, this, getObjects()) == true){
        return false;
    }
    return true;
}

void NpcObject::calculateAngle()
{
    double angle;
    double r;
    int height_game_spase = Options::instance()->app_option.getGameSpaceHeight();
    //int width_game_spase = Options::instance()->app_option.getGameSpaceWid();

    r = static_cast<int>(sqrt(pow((my_object_->getX() - getX()),2) +
                                  pow(((height_game_spase - my_object_->getY()) -(height_game_spase -  getY())),2)));


    if(my_object_->getY() <= getY()){
        angle = static_cast<int>(180/Pi *acos((my_object_->getX() - getX())/r));
    }
    if(my_object_->getY() > getY()){
        angle = static_cast<int>(180/Pi *acos((my_object_->getX() - getX())/r));
    }
    if(my_object_->getY() < getY()){
        angle = 360 - angle;
    }
    setAngle(angle);
}

