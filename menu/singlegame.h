#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QWidget>
#include <QGraphicsView>
#include "../game/engine.h"
#include "../game/graphic.h"
//#include "../game/scene.h"
#include "windowsmanager.h"

class Graphic;

class SingleGame : public QWidget
{    
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = 0);
    ~SingleGame();
signals:

public slots:
    void newGame_slot();
    void loadGame_slot();
    void saveGame_slot();
    void mainMenu_slot();
protected:
    virtual void keyPressEvent(QKeyEvent *key);
private:
    QVBoxLayout main_layout_;
    QPushButton new_game_button_;
    QPushButton load_game_button_;
    QPushButton save_game_button_;
    QPushButton main_menu_button_;
    Engine *engine_;
    Graphic *graphic_;
};

#endif // SINGLEGAME_H
