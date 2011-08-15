#include <QApplication>
#include "mainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainWindow *obj = new mainWindow();
    obj->show();
    return app.exec();
}

