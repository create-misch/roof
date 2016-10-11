#include "wall.h"

Wall::Wall()
{
    setHeight(Options::instance()->game_option.getWallHeight());
    setWidth(Options::instance()->game_option.getWallWidth());
}

Wall::~Wall()
{

}

void Wall::initWall(const int x, const int y)
{
   setHealth(100);
   setTypeObject(WALL);   
   setX(x);
   setY(y);
   setIsLife(true);
}

bool Wall::intersectOnObjects(const int x, const int y, QVector<Object *> * const npcs)
{
    QRect this_npc_rect(x, y, getWidth(), getHeight());
    for(QVector<Object *>::const_iterator it = npcs->begin(); it != npcs->end(); it++){
        if(this != *it){
            Object *obj = *it;
            QRect npc_rect(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight());
            if(this_npc_rect.intersects(npc_rect)){
                return true;
            }
        }
    }
    return false;
}
