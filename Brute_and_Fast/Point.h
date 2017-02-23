

#ifndef Point_h
#define Point_h
#include <iostream>

using namespace std;

class Point{
private:
    int x;
    int y;
public:
    //constructors.
    Point(): x(0), y(0) {}
    Point(int posX, int posY):x(posX), y(posY) {}
    Point(const Point& p): x(p.getX()), y(p.getY()) {}
    //nothing has to be done. No dynamic allocation.
    ~Point() {}
    
    //getX: get x position.
    int getX() const {return x;}
    //getY: get Y position.
    int getY() const {return y;}
    //setX: can reset the value of x position.
    void setX(int newX) { x = newX;}
    //setY: can reset the value of y position.
    void setY(int newY) { y = newY;}
    //slope: static method can be used to calculate the slope between two points.
    static double slope(const Point& p1, const Point& p2);
    //slopeTo: it can return the slope between this point to other point.
    double slopeTo(const Point& p) const;
    
    //overload operators.
    friend bool operator<(const Point& p1, const Point& p2);
    friend bool operator>(const Point& p1, const Point& p2);
    friend bool operator==(const Point& p1, const Point& p2);
    friend ostream& operator<<(ostream& os, const Point& p);
    Point operator-(const Point& p);
    Point operator+(const Point& p);
    void operator=(const Point& p);
};


#endif 
