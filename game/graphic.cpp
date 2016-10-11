#include "graphic.h"

Graphic::Graphic(QWidget *parent) : QWidget(parent)
{
    game_option = &Options::instance()->game_option;
    app_options = &Options::instance()->app_option;
    resize(app_options->getWindowWidth(), app_options->getWindowHeight());
    game_panel = new GamePanel;
    game_panel->setParent(this);
    game_panel->setGeometry(0, app_options->getGameSpaceHeight(), app_options->getGamePanelWidth(),
                           app_options->getGamePanelHeight());

    memset(&dataEngine, 0, sizeof(DataEngine));

    bot.load(":/game/bot.jpg");
    /*
    QPainter p;
    bot.load("bot.jpg");
    p.drawImage(0,0,bot);
    */


}

Graphic::~Graphic()
{
    delete game_panel;
}

void Graphic::drawGameSpase()
{
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    painter.drawRect(0, 0, app_options->getGameSpaceWidth(), app_options->getGameSpaceHeight());
    painter.drawRect(0, app_options->getGameSpaceHeight() ,
                                       app_options->getGamePanelWidth(), app_options->getGamePanelHeight());
}

void Graphic::drawMyObject(const MyObject *my)
{
    if(my == 0){
        return;
    }  
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    painter.drawRect(my->getX(), my->getY(),
                     my->getWidth(),my->getHeight());
    painter.drawLine(my->getX() + my->getWidth()/2, my->getY(),
                     my->getX() + my->getWidth()/2, my->getY() + my->getHeight()/2);//рисум ствол

}

void Graphic::drawObjects(QVector<Object *> *objects)
{
    if(objects == 0){
        return;
    }
    QVector<Object *>::const_iterator it;
    for(it = objects->begin(); it != objects->end(); it++){
        Object *obj = *it;
        if(obj->getIsLife() == true){
            switch(obj->getTypeObject()){
            case BULLET:
                drawBullet(obj);
                break;
            case BOT:
                drawBot(obj);
                break;
            case KAMIKAZE:
                drawKamikaze(obj);
            case WALL:
                drawWall(obj);
                break;
            case FAT_BOT:
                drawFatBot(obj);
                break;
            }

        }
    }
}

void Graphic::drawBullet(Object *b)
{
    if(b == 0){
        return;
    }    
    Bullet * bullet = dynamic_cast<Bullet*>(b);
        if(bullet->getIsLife() == true){
            switch(bullet->getWeapon()){
            case PISTOL:                
                painter.setPen(Qt::NoPen);
                painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                painter.drawRect(bullet->getX(), bullet->getY(), bullet->getWidth(), bullet->getHeight());
                break;
            case UZI:                
                painter.setPen(Qt::NoPen);
                painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                painter.drawRect(bullet->getX(), bullet->getY(), bullet->getWidth(), bullet->getHeight());
                painter.drawRect(bullet->getX() + bullet->getWidth(), bullet->getY(), bullet->getWidth(), bullet->getHeight());
                break;
            case ROCKET:
                painter.setPen(Qt::NoPen);
                painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.drawRect(bullet->getX(), bullet->getY(), bullet->getWidth(), bullet->getHeight());
            default:
                break;
            }
        }
}

void Graphic::drawBot(const Object *obj)
{
    painter.setPen(QPen(Qt::black,Qt::SolidLine));
    painter.drawRect(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight());

}

void Graphic::drawKamikaze(const Object *obj)
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
    painter.drawRect(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight());
}

void Graphic::drawFatBot(const Object *obj)
{
    painter.setPen(QPen(Qt::black,Qt::SolidLine));
    painter.drawPixmap(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight(),bot);
//    painter.drawRect(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight());
}

void Graphic::drawWall(const Object *obj)
{
    painter.drawRect(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight());
}


void Graphic::paintEvent(QPaintEvent *p)
{
    painter.begin(this);
    drawGameSpase();
    drawMyObject(dataEngine.my);
    drawObjects(dataEngine.objects);    
    painter.end();
}

void Graphic::keyPressEvent(QKeyEvent *k)
{
    switch(k->key())
    {
    case Qt::Key_W:
        action = UP;
        emit sendMyAction_signal(action);
        break;
    case (Qt::Key_A):
        action = LEFT;
        emit sendMyAction_signal(action);
        break;
    case (Qt::Key_S):
        action = DOWN;
        emit sendMyAction_signal(action);
        break;
    case (Qt::Key_D):
        action = RIGHT;
        emit sendMyAction_signal(action);
        break;
    case (Qt::Key_Space):
        action = SHOT;
        emit sendMyAction_signal(action);
        break;
    case (Qt::Key_N):
        action = PREVIE_WEAPON;
        emit sendMyAction_signal(action);
        break;
    case (Qt::Key_M):
        action = NEXT_WEAPON;
        emit sendMyAction_signal(action);
        break;
    case Qt::Key_P:
        emit sendPause_signal();
        break;
    case Qt::Key_Escape:
        emit sendPause_signal();
        WindowsManager::instance()->showPrevie();
        break;
    default:
        break;


    }
}

void Graphic::getState_slot(DataEngine data)
{
    dataEngine = data;
    game_panel->setParam(data);
    repaint();
}
