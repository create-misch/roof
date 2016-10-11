#include "kamikaze.h"

Kamikaze::Kamikaze():
    NpcObject()
{

}

Kamikaze::~Kamikaze()
{

}

void Kamikaze::initNpcObject(Object *const my, QVector<Object *> *const objects)
{
    setTypeObject(KAMIKAZE);
    if(my != 0){
        setMyObject(my);
    }
    if(objects != 0){
        setObjects(objects);
    }
    setAngle(1000);
    setHealth(Options::instance()->game_option.getKamikazeHealth());
    setStep(Options::instance()->game_option.getKamikazeStep());
    setIsLife(true);


}

bool Kamikaze::hintMyObject(const int x,const int y)
{
    QRect my_rect(getMyObject()->getX(), getMyObject()->getY(),getMyObject()->getWidth(), getMyObject()->getHeight());
    QRect npc_rect(x, y, getWidth(), getHeight());
    if(my_rect.intersects(npc_rect)){
        if(getMyObject()->getHealth() <= 0){
            getMyObject()->setIsLife(false);
            return true;
        }
        getMyObject()->addHealth(-20);
        setIsLife(false);
        return true;
    }
    return false;
}
