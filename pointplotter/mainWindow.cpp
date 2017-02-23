#include "mainWindow.h"
#include "Point.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qmenubar.h>
#include <QWidget>
#include <qfile.h>
#include <QString>
#include <QPainter>
#include <ctime>
#include <QSizePolicy>
#include <algorithm>
#define MAX_X 32768
#define MAX_Y 32768
#define MIN_X 0
#define MIN_Y 0


mainWindow::mainWindow(const char* fileName, QWidget*, const char*) {
    ifstream fin(fileName);
    assert(fin.is_open());
    int numOfNodes;
    fin >> numOfNodes;
    pointList temp(numOfNodes);
    pList = temp;
    int x, y;
    
    while ((fin >> x >> y)){
        Point p(x ,y);
        pList.insert(p);
    }
    fin.close();
    
    //set the background to be white, such that the points could be seen more clearly.
    setBackgroundRole(QPalette::Base);
    
    //set a minimum size, such that it could not be shrunk too small.
    setMinimumSize(500, 500);
    creatActions();
    creatMenus();
    
}

mainWindow::~mainWindow(){

}

void mainWindow::fast(){
    //use clock_t to record the time starting and ending the computation, and the difference between them is the time cost to compute.
    clock_t last, cur;
    last = clock();
    pList.fastFind();
    cur = clock();
    //pop up the window showing the time cost.
    QMessageBox::information( this, "Running time",QString("%1 ms").arg(1000.0 * (cur - last) / CLOCKS_PER_SEC, 0, 'f', 2) );
    this->repaint();
    
}

void mainWindow::brute(){
    //use clock_t to record the time starting and ending the computation, and the difference between them is the time cost to compute.
    clock_t last, cur;
    last = clock();
    pList.bruteFind();
    cur = clock();
    //pop up the window showing the time cost.
    QMessageBox::information( this, "Running time",QString("%1 ms").arg(1000.0 * (cur - last) / CLOCKS_PER_SEC, 0, 'f', 2) );
    this->repaint();
}

void mainWindow::paintEvent(QPaintEvent*){
    
    QPainter painter(this);
    Point pStart, pEnd;
    pointList::Iterator itr = pList.lineIterator();
    pointList::pointIterator itr2 = pList.pointIter();
    for(int i = 0; i !=pList.numOfPoints(); ++i, ++itr2){
        painter.drawPoint((*itr2).getX(),(*itr2).getY());
	//the point is too small to be seen, such that I draw circles with a small radius to represent the points.
	//and I shift the circles a little bit, such that the centers of the circle are the position of points.
	
	//for the coordinate system of QT is the flipped version of the normal one.
	//so we need to flip back the y coordinate.
	//for integer precision is enough to plot the points and lines.
	
	//and we rescale the x and y, so that it fit the window.
	
	int x = (*itr2).getX()*(this->width()) / MAX_X - 1;
	int y = this->height() - (*itr2).getY()*(this->height())/ MAX_Y-1;
	painter.drawEllipse(x ,y ,2,2);
    }
    
    for(int i = 0; i != pList.numOfLines(); ++i, ++itr){
	//in case brute force method is used, we sort the points in each line.
	//such that we can print out the line more easily.
	(*itr).order();
        pStart = (*itr).head();
        pEnd = (*itr).tail();
	//for the coordinate system of QT is the flipped version of the normal one.
	//so we need to flip back the y coordinate.
	//for integer precision is enough to plot the points and lines.
	
	//and we rescale the x and y, so that it fit the window.
	
	int startX = pStart.getX() *(this->width()) / MAX_X;
	int startY =this->height() - pStart.getY() *(this->height())/ MAX_Y;
	int endX = pEnd.getX()*(this->width())/ MAX_X;
	int endY =this->height() - pEnd.getY()*(this->height()) / MAX_Y;
	//here we have taken the advantage of ordered points in lines.
        painter.drawLine( startX, startY,endX, endY );
    }
}

void mainWindow::creatActions(){
    //create the menu and the corresponding action.
    fastAct = new QAction(tr("&fast"), this);
    fastAct->setStatusTip(tr("Fast way!"));
    connect(fastAct, SIGNAL(triggered()), this, SLOT(fast()));
    bruteAct = new QAction(tr("&brute force"), this);
    bruteAct->setStatusTip(tr("Slow way!"));
    connect(bruteAct, SIGNAL(triggered()), this, SLOT(brute()));
}

void mainWindow::creatMenus(){
    //create the menubar.
    Menu = menuBar()->addMenu(tr("&Menu"));
    Menu->addAction(fastAct);
    Menu->addAction(bruteAct);
}


