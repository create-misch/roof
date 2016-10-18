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
