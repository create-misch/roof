#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QFileDialog>
#include "./objects/bullet.h"
#include "./objects/myobject.h"
#include "./objects/bot.h"
#include "./objects/kamikaze.h"
#include "./objects/wall.h"
#include "./objects/fatbot.h"
#include "level.h"
#include "reader/levelsreader.h"
#include "algorithm"

typedef QVector<Object *> ObjectVector;

bool sortLife_false(Object *lhs, Object *rhs);
bool isLife_false(Object *o);
bool isLifeNpc_true(Object *o);

class Wall;

struct DataEngine{
    MyObject *my;
    QVector<Object *> *objects;
    int level;
    int score;
};

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);
    virtual ~Engine();
    void initEngine();
    void newSingleGame(const int level);
    void start();
    void pause();
    void stop(){}
    bool isRunning() const;
//    int saveGame(){}
//    int loadGame(){}
    bool readLevels();
private:
    void endGame();
    void gameOver();
    void nextLevel();
    void initLevel(const int level);
    void initWalls();

    void clearTrash();//очистка всех контейнеров

    //Каждый такт
    void burnNpc(const int level);
    void checkHints();
    void checkLife();
    void checkNextLevel(const int level);
    void moveAll();//перемещение всех объектов
    void sendDataEngine();



    QVector<Level> levels_;
    QTimer timer_;
    MyObject my_object_;
    ObjectVector objects_;
    bool is_running_;
    int level_;
    int burned_npc_;
    int score_;
    qint64 time_end_level_;


signals:
    void sendState_signal(const DataEngine data);
    void sendAction_signal(const Action a);

public slots:
    void everyTick_slot();
    void getPause_slot();

};

#endif // ENGINE_H
