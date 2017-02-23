#include "Point.h"

double Point::slope(const Point& p1, const Point& p2){
    double s;
    double xDiff = p2.getX() - p1.getX();
    double yDiff = p2.getY()- p1.getY();
    //this is the definition of the slope.
    s = yDiff/xDiff;
    return s;
}

double Point::slopeTo(const Point& p) const{
    //use static method to impelment the slopeTo.
    return slope(p, *this);
}


ostream& operator<<(ostream& os, const Point& p){
    os<< "(" <<p.getX() << ", "<< p.getY()<< ")";
    return os;
}

//in achieve minimal representation, we implement operator< so that points can be ordered during searching, and then we can insert points into a line in a ordered way.
bool operator<( const Point& p1, const Point& p2){
    if(p1.getX() == p2.getX()){
        return p1.getY() < p2.getY();
    }
    return p1.getX() < p2.getX();
}

//in achieve minimal representation, we implement operator< so that points can be ordered during searching, and then we can insert points into a line in a ordered way.
bool operator>( const Point& p1, const Point& p2){
    if(p1.getX() == p2.getX()){
        return p1.getY() > p2.getY();
    }
    return p1.getX() > p2.getX();
}

//in achieve minimal representation, we implement operator< so that points can be ordered during searching, and then we can insert points into a line in a ordered way.
bool operator==(const Point& p1, const Point& p2){
    return (p1.getX() == p2.getX() && p1.getY() == p2.getY());
}


Point Point::operator-(const Point& p){
    int newX =x - p.getX();
    int newY =y - p.getY();
    Point temp(newX,newY);
    return temp;
}

Point Point::operator+(const Point& p){
    int newX = x + p.getX();
    int newY = y + p.getY();
    Point temp(newX ,newY );
    return temp;
}

void Point::operator=(const Point& p){
    x = p.getX();
    y = p.getY();
}
