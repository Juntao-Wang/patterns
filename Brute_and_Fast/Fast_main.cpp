
#include <iostream>
#include <fstream>
#include <assert.h>
#include <ctime>
#include <time.h>
#include "Point.h"
#include "pointList.h"
#include "Fast.h"

using namespace std;

int main(int argc, const char * argv[]) {
    int numOfNodes;
    cin >> numOfNodes;
    Fast f(numOfNodes);
    int x, y;
    while ((cin >> x >> y)){
        Point p(x ,y);
        f.insert(p);
    }
    f.fast();
    
    
    return 0;
}
