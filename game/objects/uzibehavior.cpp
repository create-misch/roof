#include "uzibehavior.h"

UziBehavior::UziBehavior() :
    BulletBehavior(UZI)
{

}

UziBehavior::~UziBehavior()
{

}

void UziBehavior::hintInObject(Object *const npc)
{    
    npc->addHealth(-30);
    if(npc->getHealth() <= 0){
        npc->setIsLife(false);
    }
}
