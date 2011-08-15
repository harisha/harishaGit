#include <QApplication>
#include "myVlcPlayer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    myVlcPlayer *obj = new myVlcPlayer(); 
    obj->show(); 
    return app.exec();
}
