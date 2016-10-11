#ifndef OPTIONS_H
#define OPTIONS_H
#include <QPushButton>
#include <QWidget>
#include <QVector>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>
#include <QCoreApplication>
#include <QLabel>


class AppOptions
{
public:
    AppOptions(){}
    int window_height;// = 400;
    int window_width;// = 600;
    int getWindowHeight(){return 600;}
    int getWindowWidth(){return 800;}
    int getButtonHeight(){return 50;}
    int getButtonWidth(){return 200;}
    int getGameSpaceHeight(){return 580;}
    int getGameSpaceWidth(){return 800;}
    int getGamePanelHeight(){return 20;}
    int getGamePanelWidth(){return 800;}

};

class GameOptions
{
public:
    GameOptions() {}
    int getMyObjectHeight(){return 40;}
    int getMyObjectWidth(){return 40;}
    int getMyStep(){return 5;}
    int getMyHealth(){return 100;}
    int getNpcHeight(){return 40;}
    int getNpcWidth(){return 40;}
    int getBotStep(){return 1;}
    int getBotHealth(){return 100;}
    int getKamikazeStep(){return 5;}
    int getKamikazeHealth(){return 10;}
    int getFatBotStep(){return 1;}
    int getFatBotHealth(){return 200;}
    int getBulletHeight(){return 3;}
    int getBulletWidth(){return 3;}
    int getBulletStep(){return 20;}
    int getWallHeight(){return 40;}
    int getWallWidth(){return 40;}
    int getRocketHintHeight(){return 100;}
    int getRocketHintWidth(){return 100;}
    int getTimePrevieFight(){return 3000;}//время на подготовку перед след уровнем

};

class Options
{
public:
    static Options *instance();
    AppOptions app_option;
    GameOptions game_option;

protected:
    Options();

private:
    static Options *_options;

};

#endif // OPTIONS_H
