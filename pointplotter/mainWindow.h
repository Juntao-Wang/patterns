#include "Point.h"
#include "pointList.h"
#include <qmainwindow.h>
#include <qapplication.h>

#ifndef mainWindow_h
#define mainWindow_h
class mainWindow : public QMainWindow{
    Q_OBJECT
    
public:
    mainWindow();
    mainWindow(const char*, QWidget* parent = 0, const char* name = 0);
    virtual ~mainWindow();
    
public slots:
    void brute();
    
    void fast();
    
private:
    pointList pList;
    QMenu* Menu;
    QAction* bruteAct;
    QAction* fastAct;
    
    void creatActions();
    void creatMenus();
protected:
    virtual void paintEvent(QPaintEvent*);
    
};
#endif
