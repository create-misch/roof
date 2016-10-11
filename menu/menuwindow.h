#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>

#include "../options.h"
#include "windowsmanager.h"
#include "singlegame.h"



class MenuWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWindow(QWidget *parent = 0);
    ~MenuWindow();
    Options *option;
    void keyPressEvent(QKeyEvent *ev);

signals:

public slots:
    void single_game_slot();
    void network_game_slot();
    void setting_slot();
    void quit_slot();

private:            
    QPushButton single_game_button_;
    QPushButton network_game_button_;
    QPushButton settings_button_;
    QPushButton quit_button_;
    QVBoxLayout main_layout_;

};

#endif // MENUWINDOW_H
