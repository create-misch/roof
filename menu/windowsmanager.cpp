#include "windowsmanager.h"

WindowsManager *WindowsManager::windows_manager_ = 0;

WindowsManager::WindowsManager()
{
    /*
    connect(menu_window_, SIGNAL(pop_window_signal()),SLOT(popBackWindow()));
    connect(menu_window_, SIGNAL(push_window_signal(QWidget*)),SLOT(pushBackWindow(QWidget*)));
    menu_window_ = new MenuWindow;
    pushBackWindow(menu_window_);
    */
}

WindowsManager *WindowsManager::instance()
{
    if(windows_manager_ == 0){
        windows_manager_ = new WindowsManager;
    }
    return windows_manager_;
}

void WindowsManager::pushBackWindow(QWidget *window)
{

    if(windows_.size() > 1){
        windows_.last()->hide();
    }
    if(windows_.isEmpty() == true){
        windows_.push_back(window);
        //windows_.last()->show();
        //windows_.last()->resize(Options::instance()->app_option.getWindowWidth(),
           //                     Options::instance()->app_option.getWindowHeight());
        QWidget *widget = new QWidget;
        windows_.push_front(widget);
        windows_.last()->resize(Options::instance()->app_option.getWindowWidth(),
                                Options::instance()->app_option.getWindowHeight());        
        windows_.last()->setParent(windows_.first());
        windows_.first()->show();
    }
    else{
        window->setParent(windows_.first());
        windows_.push_back(window);
        windows_.last()->setGeometry(0, 0, Options::instance()->app_option.getWindowWidth(),
                                Options::instance()->app_option.getWindowHeight());
    }



    windows_.last()->show();
    windows_.last()->setFocus();
}

void WindowsManager::popBackWindow()
{
    if(windows_.size() > 2){
        delete windows_.last();
        windows_.pop_back();
        if(windows_.empty() == false){
            windows_.last()->show();
            windows_.last()->setFocus();
        }
    }
}

void WindowsManager::showPrevie()
{
    if(windows_.size() > 2){
        windows_.last()->hide();
        QVector<QWidget *>::iterator it = windows_.end();
        it -= 2;
        (*it)->show();
        (*it)->setFocus();
    }
}

void WindowsManager::showNext()
{
    if(windows_.size() > 2){
        QVector<QWidget *>::iterator it = windows_.end();
        it -= 2;
        (*it)->hide();
        windows_.last()->show();
        windows_.last()->setFocus();
    }
}
