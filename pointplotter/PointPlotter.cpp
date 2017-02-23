//#include <qapplication>
#include <fstream>
#include <iostream>
#include <assert.h>
#include "mainWindow.h"

int main(int argc, char* argv[]){
    QApplication a(argc, argv);
    assert(argc >1);
    QWidget* w = new mainWindow(argv[1]);
    w->show();
    return a.exec();
};
