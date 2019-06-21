//#include <QApplication>
//#include "widgets.h"

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    MyWidget widget;
//    widget.show();
//    return app.exec();
//}


#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    Q_INIT_RESOURCE(dockwidgets);
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}