#include "Fast.h"
#include <iostream>
using namespace std;

void Fast::fast(){
    pointList::fastFind();
    pointList::Iterator itr = this->lineIterator();
    for (int i = 0; i != numOfLines(); ++i, ++itr){
        cout <<itr->numOfPoints() << ": "<< *itr <<endl;
    }
}
