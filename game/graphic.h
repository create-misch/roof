#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QImage>
#include "engine.h"
#include "../options.h"
#include "gamepanel.h"
#include "../menu/windowsmanager.h"

class Graphic : public QWidget
{
    Q_OBJECT
public:
    explicit Graphic(QWidget *parent = 0);
    ~Graphic();
    void drawGameSpase();
    void drawMyObject(const MyObject *my);
    void drawObjects(QVector<Object *> *objects);
    void drawBullet(Object *b);
    void drawBot(const Object *obj);
    void drawKamikaze(const Object *obj);
    void drawFatBot(const Object *obj);
    void drawWall(const Object *obj);

    QPixmap bot;

    Action action;
    DataEngine dataEngine;
    GamePanel *game_panel;
    QPainter painter;
    GameOptions *game_option;
    AppOptions *app_options;

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

signals:
    void sendMyAction_signal(Action action);
    void sendPause_signal();
public slots:
    void getState_slot(DataEngine data);
};

#endif // GRAPHIC_H
