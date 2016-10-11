#ifndef WINDOWSMANAGER_H
#define WINDOWSMANAGER_H


#include "../options.h"
#include "menuwindow.h"

#include <QWidget>

class WindowsManager
{
public:
    static WindowsManager *instance();
    void pushBackWindow(QWidget *window);
    void popBackWindow();
    void showPrevie();
    void showNext();

protected:
    WindowsManager();

private:
    static WindowsManager *windows_manager_;
    QVector<QWidget *> windows_;

};

#endif // WINDOWSMANAGER_H
