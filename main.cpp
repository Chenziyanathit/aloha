#include <QApplication>
#include "mainwindow.h"
//extern Topo::pos_xyz new_posxyz[100];


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    
    return a.exec();
}
