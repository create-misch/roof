#include <QApplication>
#include "./menu/windowsmanager.h"
#include "./menu/menuwindow.h"
#include "./game/engine.h"
#include "./game/graphic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WindowsManager::instance();
    MenuWindow *menu_window = new MenuWindow;
    WindowsManager::instance()->pushBackWindow(menu_window);

    //w.show();


    /*
    Engine engine;
    engine.initEngine();
    engine.newSingleGame(1);

    Graphic graphic;// = new Graphic;

    QObject::connect(&engine, SIGNAL(sendState_signal(DataEngine)), &graphic, SLOT(getState_slot(DataEngine)));
    QObject::connect(&graphic, SIGNAL(sendMyAction(Action)), &engine, SIGNAL(sendAction_signal(Action)));

    graphic.show();
    //graphic->setFocus();
    //graphic->activateWindow();
*/

    return a.exec();
}
