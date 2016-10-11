#include "menuwindow.h"


MenuWindow::MenuWindow(QWidget *parent) :
    QWidget(parent)
{

    option = Options::instance();

    single_game_button_.setText("Single Game");
    single_game_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    single_game_button_.setParent(this);
    connect(&single_game_button_, SIGNAL(clicked()), SLOT(single_game_slot()));

    network_game_button_.setText("Network Game");
    network_game_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    network_game_button_.setParent(this);
    connect(&network_game_button_, SIGNAL(clicked()), SLOT(network_game_slot()));

    settings_button_.setText("Settings");
    settings_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    settings_button_.setParent(this);
    connect(&settings_button_, SIGNAL(clicked()), SLOT(setting_slot()));

    quit_button_.setText("Quit");
    quit_button_.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    quit_button_.setParent(this);
    connect(&quit_button_, SIGNAL(clicked()), SLOT(quit_slot()));

    main_layout_.setMargin(Options::instance()->app_option.getWindowHeight()/5);
    main_layout_.setSpacing(Options::instance()->app_option.getWindowHeight()/10);

    main_layout_.addWidget(&single_game_button_);
    main_layout_.addWidget(&network_game_button_);
    main_layout_.addWidget(&settings_button_);
    main_layout_.addWidget(&quit_button_);
    setLayout(&main_layout_);

}

MenuWindow::~MenuWindow()
{

}


void MenuWindow::single_game_slot()
{
    SingleGame *single_game = new SingleGame;
    WindowsManager::instance()->pushBackWindow(single_game);
}

void MenuWindow::network_game_slot()
{

}

void MenuWindow::setting_slot()
{
    //emit push_window_signal();
}

void MenuWindow::quit_slot()
{
    QCoreApplication::exit(0);
}

void MenuWindow::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key()){
    case Qt::Key_Escape:

        break;


    }
}
