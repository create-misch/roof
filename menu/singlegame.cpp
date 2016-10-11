#include "singlegame.h"

SingleGame::SingleGame(QWidget *parent) : QWidget(parent)
{
    new_game_button_.setText("New Game");
    new_game_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(&new_game_button_, SIGNAL(clicked(bool)), SLOT(newGame_slot()));

    load_game_button_.setText("Load Game");
    load_game_button_.setParent(this);
    load_game_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(&load_game_button_, SIGNAL(clicked(bool)),SLOT(loadGame_slot()));

    save_game_button_.setText("Save Game");
    save_game_button_.setParent(this);
    save_game_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(&save_game_button_, SIGNAL(clicked(bool)), SLOT(saveGame_slot()));

    main_menu_button_.setText("Main menu");
    main_menu_button_.setParent(this);
    main_menu_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(&main_menu_button_, SIGNAL(clicked(bool)), SLOT(mainMenu_slot()));


    main_layout_.setMargin(Options::instance()->app_option.getWindowHeight()/5);
    main_layout_.setSpacing(Options::instance()->app_option.getWindowHeight()/10);


    main_layout_.addWidget(&new_game_button_);
    main_layout_.addWidget(&save_game_button_);
    main_layout_.addWidget(&load_game_button_);
    main_layout_.addWidget(&main_menu_button_);
    setLayout(&main_layout_);

    engine_ = 0;
    graphic_ = 0;

}

SingleGame::~SingleGame()
{

}

void SingleGame::newGame_slot()
{
    if((engine_ != 0) || (graphic_ != 0)){
        return;
    }
    graphic_ = new Graphic;
    graphic_->setParent(this);

    engine_ = new Engine;
    engine_->initEngine();
    engine_->newSingleGame(1);



    connect(engine_, SIGNAL(sendState_signal(DataEngine)), graphic_, SLOT(getState_slot(DataEngine)));
    connect(graphic_, SIGNAL(sendMyAction_signal(Action)), engine_, SIGNAL(sendAction_signal(Action)));
    connect(graphic_, SIGNAL(sendPause_signal()), engine_, SLOT(getPause_slot()));

    WindowsManager::instance()->pushBackWindow(graphic_);
    //graphic.show();

}

void SingleGame::loadGame_slot()
{

}

void SingleGame::saveGame_slot()
{

}

void SingleGame::mainMenu_slot()
{
    if(engine_ != 0){
        delete engine_;
    }
    if(graphic_ != 0){
        WindowsManager::instance()->popBackWindow();
    }
    WindowsManager::instance()->popBackWindow();
}

void SingleGame::keyPressEvent(QKeyEvent *key)
{
    switch(key->key()){
    case Qt::Key_Escape:
        WindowsManager::instance()->showNext();
        engine_->start();
        break;
    }
}
