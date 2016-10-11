#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QWidget>
#include <QLabel>
#include "engine.h"
#include <QHBoxLayout>

class GamePanel : public QWidget
{
    Q_OBJECT
public:
    explicit GamePanel(QWidget *parent = 0);
    ~GamePanel(){}
    QHBoxLayout layout;
    QLabel level_txt;
    QLabel level_count;
    QLabel health_txt;
    QLabel health_count;
    QLabel weapon_txt;
    QLabel weapon_count;
    QLabel ammunition_txt;
    QLabel ammunition_count;
    QLabel score_txt;
    QLabel score_count;
    void setParam(const DataEngine data);
signals:

public slots:
};

#endif // GAMEPANEL_H
