#include "Brute.h"
#include <iostream>

using namespace std;

void Brute::brute(){
    pointList::bruteFind();
    pointList::Iterator itr = pointList::lineIterator();
    for (int i = 0; i != pointList::numOfLines(); ++i, ++itr){
        cout <<itr->numOfPoints() << ": "<< *itr <<endl;
    }
    
}
