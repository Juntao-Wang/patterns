#ifndef Fast_h
#define Fast_h

#include "pointList.h"
#include <iostream>

using namespace std;

class Fast : public pointList{
public:
    //constructors.
    Fast(): pointList() {}
    Fast(int size): pointList(size) {}
    //destructor calls the base destructor is enough.
    //for no derived data memeber.
    ~Fast() {}
    
    void fast();
};
#endif
