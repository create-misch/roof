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

    if(!my_pixmap.load(":/game/my.jpg")){
        qDebug() << "don't load my tank";
    }

    if(!fat_bot.load(":/game/fatbot.jpg")){
        qDebug() << "don't load fat bot";
    }

    if(!kamikaze.load(":/game/kamikaze.jpg")){
        qDebug () << "don't load kamikaze";
    }

    if(!bot.load(":/game/bot.jpg")){
        qDebug () << "don't load bot";
    }

    if(!wall.load(":/game/box.gif")){
        qDebug () << " don't load wall";
    }

}

Graphic::~Graphic()
{
    delete game_panel;
}

void Graphic::drawGameSpase()
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
//    painter.setBrush(QBrush(QColor(255,255,255), QPixmap(":/game/bg.jpg")));
    painter.drawRect(0, 0, app_options->getGameSpaceWidth(), app_options->getGameSpaceHeight());
    painter.drawRect(0, app_options->getGameSpaceHeight() ,
                                       app_options->getGamePanelWidth(), app_options->getGamePanelHeight());
    painter.end();


}

void Graphic::drawMyObject(const MyObject *my)
{
    if(my == 0){
        return;
    }  
    QPainter painter;
    painter.begin(this);

    QTransform transform;
    transform.translate(+my->getX() + my->getWidth()/2, +my->getY() + my->getHeight()/2);
    transform. rotate(+my->getAngle());
    transform.translate(-my->getX() - my->getWidth()/2, -my->getY() - my->getHeight()/2);
    painter.setWorldTransform(transform);
    painter.drawPixmap(my->getX(), my->getY(),
                     my->getWidth(),my->getHeight(), my_pixmap);

    painter.end();
}

void Graphic::drawObjects(QVector<Object *> *objects)
{
    if(objects == 0){
        return;
    }
    for(QVector<Object *>::const_iterator it = objects->begin(); it != objects->end(); it++){
        switch((*it)->getTypeObject()){
        case BULLET:
            drawBullet(*it);
            break;
        case BOT:
            drawBot(*it);
            break;
        case KAMIKAZE:
            drawKamikaze(*it);
            break;
        case WALL:
            drawWall(*it);
            break;
        case FAT_BOT:
            drawFatBot(*it);
            break;
        }
    }
}

void Graphic::drawBullet(Object *b)
{
    if(b == 0){
        return;
    }
    QPainter painter;
    painter.begin(this);

    QTransform transform;
    transform.translate(+b->getX() + b->getWidth()/2, +b->getY() + b->getHeight()/2);
    transform. rotate(+b->getAngle());
    transform.translate(-b->getX() - b->getWidth()/2, -b->getY() - b->getHeight()/2);
    painter.setWorldTransform(transform);

    Bullet * bullet = dynamic_cast<Bullet*>(b);
        if(bullet->getIsLife() == true){
            switch(bullet->getWeapon()){
            case PISTOL:                
                painter.setPen(QPen(Qt::black,Qt::SolidLine));
                painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
                painter.drawEllipse(bullet->getX(), bullet->getY(), bullet->getWidth(), bullet->getHeight());
                break;
            case UZI:                
                painter.setPen(QPen(Qt::black,Qt::SolidLine));
                painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
                painter.drawEllipse(bullet->getX(), bullet->getY(), bullet->getWidth(), bullet->getHeight());
                painter.drawEllipse(bullet->getX() + bullet->getWidth(), bullet->getY(), bullet->getWidth(), bullet->getHeight());
                break;
            case ROCKET:
                painter.setPen(QPen(Qt::black,Qt::SolidLine));
                painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.drawEllipse(bullet->getX(), bullet->getY(), bullet->getWidth(), bullet->getHeight());
            default:
                break;
            }
        }
        else{
            if(bullet->getWeapon() == ROCKET){
                painter.setPen(QPen(Qt::black,Qt::SolidLine));
                painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.drawEllipse(QPoint(bullet->getX(), bullet->getY()), game_option->getRocketHintWidth(),
                                    game_option->getRocketHintHeight());
            }
        }
    painter.end();

}

void Graphic::drawBot(const Object *obj)
{
    if(obj->getIsLife() == true){
        QPainter painter;
        painter.begin(this);

        QTransform transform;
        transform.translate(+obj->getX() + obj->getWidth()/2, +obj->getY() + obj->getHeight()/2);
        transform. rotate(+obj->getAngle());
        transform.translate(-obj->getX() - obj->getWidth()/2, -obj->getY() - obj->getHeight()/2);
        painter.setWorldTransform(transform);

        painter.setPen(QPen(Qt::black,Qt::SolidLine));
        painter.drawPixmap(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight(), bot);
        painter.end();
    }
}

void Graphic::drawKamikaze(const Object *obj)
{
    if(obj->getIsLife() == true){
        QPainter painter;
        painter.begin(this);
        painter.save();

        QTransform transform;
        transform.translate(+obj->getX() + obj->getWidth()/2, +obj->getY() + obj->getHeight()/2);
        transform. rotate(+obj->getAngle());
        transform.translate(-obj->getX() - obj->getWidth()/2, -obj->getY() - obj->getHeight()/2);
        painter.setWorldTransform(transform);

        painter.setPen(QPen(Qt::black,Qt::SolidLine));
        painter.drawPixmap(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight(), kamikaze);
        painter.restore();
        painter.end();
    }
}

void Graphic::drawFatBot(const Object *obj)
{
    if(obj->getIsLife() == true){



        QPainter painter;
        painter.begin(this);
        painter.setPen(QPen(Qt::black,Qt::SolidLine));

        QTransform transform;
        transform.translate(+obj->getX() + obj->getWidth()/2, +obj->getY() + obj->getHeight()/2);
        transform. rotate(+obj->getAngle());
        transform.translate(-obj->getX() - obj->getWidth()/2, -obj->getY() - obj->getHeight()/2);
        painter.setWorldTransform(transform);

        painter.drawPixmap(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight(),fat_bot);
        painter.end();
    }
}

void Graphic::drawWall(const Object *obj)
{
    if(obj->getIsLife() == true){
        QPainter painter;
        painter.begin(this);
        painter.setPen(QPen(Qt::black,Qt::SolidLine));
        painter.drawPixmap(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight(), wall);
        painter.end();
    }
}


void Graphic::paintEvent(QPaintEvent *p)
{
    drawGameSpase();
    drawMyObject(dataEngine.my);
    drawObjects(dataEngine.objects);
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

    }
}

void Graphic::getState_slot(DataEngine data)
{
    dataEngine = data;
    game_panel->setParam(data);
    repaint();
}
