#include "pistolbehavior.h"

PistolBehavior::PistolBehavior() :
    BulletBehavior(PISTOL)
{
}

PistolBehavior::~PistolBehavior()
{

}

void PistolBehavior::hintInObject(Object *const npc)
{
    npc->addHealth(-10);
    if(npc->getHealth() <= 0){
        npc->setIsLife(false);
    }
}
