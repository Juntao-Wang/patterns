#ifndef Brute_h
#define Brute_h
#include <iostream>
#include "pointList.h"

class Brute : public pointList{
public:
    //constructors.
    Brute():pointList() {}
    Brute(int size): pointList(size) {}
    //destructor calls the base destructor is enough.
    //for no derived data memeber.
    ~Brute() {}
    
    void brute();
};


#endif
