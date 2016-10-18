#include "rocketbehavior.h"

RocketBehavior::RocketBehavior():
    BulletBehavior(ROCKET)
{

}

RocketBehavior::~RocketBehavior()
{

}

void RocketBehavior::hintInObject(Object *const npc, QVector<Object *> *const objects)
{
    qDebug () << "shot rocket";
    if(objects->isEmpty() == true){
        return;
    }
    QRect rect_hint(npc->getX() - Options::instance()->game_option.getRocketHintHeight()/2,
                    npc->getY() - Options::instance()->game_option.getRocketHintWidth()/2,
                    Options::instance()->game_option.getRocketHintWidth(),
                    Options::instance()->game_option.getRocketHintHeight());
    for(QVector<Object *>::iterator it = objects->begin(); it != objects->end(); it ++){        
        if((*it)->getTypeObject() != BULLET){
            QRect rect_npc((*it)->getX(), (*it)->getY(), (*it)->getWidth(), (*it)->getHeight());
            if(rect_hint.intersects(rect_npc)){
                (*it)->addHealth(-35);
                if((*it)->getHealth() <= 0){
                    (*it)->setIsLife(false);
                }
            }
        }
    }
}
