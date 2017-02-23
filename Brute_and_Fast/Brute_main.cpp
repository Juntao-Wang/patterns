
#include <iostream>
#include <fstream>
#include <assert.h>
#include <ctime>
#include <time.h>
#include "Point.h"
#include "pointList.h"
#include "Brute.h"

using namespace std;

int main(int argc, const char * argv[]) {
    int numOfNodes;
    cin >> numOfNodes;
    Brute b(numOfNodes);
    int x, y;
    while ((cin >> x >> y)){
        Point p(x ,y);
        b.insert(p);
    }
    b.brute();
    
    
    return 0;
}
