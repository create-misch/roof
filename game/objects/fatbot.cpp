#include "fatbot.h"

FatBot::FatBot():
    NpcObject()
{

}

FatBot::~FatBot()
{

}


void FatBot::initNpcObject(Object * const my, QVector<Object *> * const objects)
{
    setTypeObject(FAT_BOT);
    if(my != 0){
        setMyObject(my);
    }
    if(objects != 0){
        setObjects(objects);
    }
    setAngle(1000);
    setHealth(Options::instance()->game_option.getFatBotHealth());
    setStep(Options::instance()->game_option.getFatBotStep());
    setIsLife(true);
}

bool FatBot::hintMyObject(const int x, const int y)
{
    if(intersectOnObjects(x, y, this, getMyObject()) == true){

        if(getMyObject()->getHealth() <= 0){
            getMyObject()->setIsLife(false);
            return true;
        }
        getMyObject()->addHealth(-2);
        return true;
    }
    return false;
}

