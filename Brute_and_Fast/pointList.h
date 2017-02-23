
#ifndef pointList_h
#define pointList_h
#include "Point.h"
#include <vector>
#include <algorithm>
using namespace std;

class line{
private:
    vector<Point> points;
public:
    //constructor.
    line(): points() {}
    //add: it can add points into this line.
    void add(const Point& p){ points.push_back(p);}
    //cleanUp: remove this line.
    void cleanUp(){points.clear();}
    //numOfPoints: return the value of points in this line.
    int numOfPoints() const {return points.size();}
    //order: this is only used to order the points in one line found by brute force.
    void order() {sort(points.begin(), points.end());}
    //head: return the value of the first point in this line.
    Point head() const {return points.front();}
    //tail: return the value of the last point in this line.
    Point tail() const {return points.back();}
    //isLine: return true if this is a line containing at least two points, else return false.
    bool isLine() const {return points.size() >=2;}
    //overload operators.
    friend bool operator==(const line& l1, const line& l2);
    friend ostream& operator<<(ostream& os, const line& l);
    
};

//functor which can be used in sorting algorithm.
class compSlopeTo{
private:
    Point ref;
public:
    //constructors.
    compSlopeTo(): ref(0, 0) {}
    compSlopeTo(const Point& p): ref(p) {}
    compSlopeTo(int x, int y): ref(x, y) {}
    //operator overload.
    bool operator()(const Point& p1, const Point& p2) const {
        if(p1.slopeTo(ref) == p2.slopeTo(ref)){
            return p1.getX() < p2.getX();
        }else{
            return (p1.slopeTo(ref)<p2.slopeTo(ref));
        }
    }
};


class pointList{
private:
    Point* array;
    int pos;
    int maxSize;
    vector<line> listOfLine;
public:
    //constructors.
    pointList(): array(new Point[0]), pos(0), maxSize(0), listOfLine() {}
    pointList(int size):array(new Point[size]), pos(0), maxSize(size), listOfLine() {}
    virtual ~pointList() {delete [] array;}
    
    //Iterator provides the iterator to manipulate the lines in this pointList.
    typedef vector<line>::iterator Iterator;
    //pointIterator provides the iterator to manipulate the points in this pointList.
    typedef Point* pointIterator;
    //lineIterator: return the iterator of listOfLine.
    Iterator lineIterator() {return listOfLine.begin(); }
    //numOfLines: return the number of lines in this pointList.
    int numOfLines() const {return listOfLine.size();}
    //numOfPoints: return the number of points in this pointList.
    int numOfPoints() const {return pos + 1;}
    //lenOfList: return the maximum number of points which can be stored.
    int lenOfList() const {return maxSize;}
    //pointIter: return the iterator of the points.
    pointIterator pointIter() {return array;}
    
    //insert: add points into this pointList.
    void insert(Point);
    //two methods to find the lines in pointList.
    void bruteFind();
    void fastFind();

    //operator overload.
    void operator=(const pointList& pl);
};


#endif
