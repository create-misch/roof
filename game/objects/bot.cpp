#include "bot.h"

Bot::Bot():
    NpcObject()
{

}

Bot::~Bot()
{

}

void Bot::initNpcObject(Object *const my,QVector<Object *> *const objects)
{
    setTypeObject(BOT);
    if(my != 0){
        setMyObject(my);
    }
    if(objects != 0){
        setObjects(objects);
    }
    setAngle(1000);
    setHealth(Options::instance()->game_option.getBotHealth());
    setStep(Options::instance()->game_option.getBotStep());
    setIsLife(true);

}

bool Bot::hintMyObject(const int x,const int y)
{
    QRect my_rect(getMyObject()->getX(), getMyObject()->getY(),getMyObject()->getWidth(), getMyObject()->getHeight());
    QRect npc_rect(x, y, getWidth(), getHeight());
    if(my_rect.intersects(npc_rect)){
        if(getMyObject()->getHealth() <= 0){
            getMyObject()->setIsLife(false);
            return true;
        }
        getMyObject()->addHealth(-1);
        return true;
    }
    return false;
}
