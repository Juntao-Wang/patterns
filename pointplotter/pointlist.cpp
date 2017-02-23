#include "pointList.h"
#include <ctime>

using namespace std;
//overload operator <<, we can print out the lines more easily.
ostream& operator<<(ostream& os, const line& l){
    for(int i = 0; i != (l.numOfPoints()); ++i){
        os << l.points[i];
        if(i+1 != (l.numOfPoints())){
            cout << " -> ";
        }
    }
    return os;
}

//overload operator ==, such that we can compare the lines more efficiently.
bool operator==(const line& l1, const line& l2){
    if(l1.isLine() && l2.isLine()){
        return (l1.head() == l2.head() && l1.tail() == l2.tail());
    }else{
        return false;
    }
}

//overload operator =, such that we could assign other line to it.
void pointList::operator=(const pointList& pl){
    //assignment operator, firstly we need to delete the previous stored array and achieve deep copy.
    delete [] array;
    maxSize = pl.lenOfList();
    pos = pl.numOfPoints() - 1;
    array = new Point[maxSize];
    for (int i = 0; i != pos + 1; ++i){
        array[i] = pl.array[i];
    }
}

void pointList::insert(Point p){
    if(pos  == maxSize){
        cout << "warning! Your input number of nodes does not coincide with the input points! Only " << maxSize << " nodes have been recorded!" <<endl;
        return;
    }
    array[pos] = p;
    pos++;
}

void pointList::bruteFind(){
    //first clean up the listOfLine.
    listOfLine.clear();
    for(int i =0; i < pos; ++i){
        for(int j = i+1; j<pos; ++j){
            for(int k = j+1; k<pos;++k){
                //first check whether three points are in a line.
                double s1, s2;
                s1 = Point::slope(array[i], array[j]);
                s2 = Point::slope(array[i], array[k]);
                if (s1 != s2 ) continue;
                //then check whether the four points are in a line.
                for(int l = k+1; l<pos;++l){
                    double s3;
                    s3 = Point::slope(array[i], array[l]);
                    if (s1 == s3){
                        line tempL;
                        tempL.add(array[i]);
                        tempL.add(array[j]);
                        tempL.add(array[k]);
                        tempL.add(array[l]);
                        listOfLine.push_back(tempL);
                    }
                }
                
            }
        }
    }
}


void pointList::fastFind(){
    //first clean up the listOfLine.
    listOfLine.clear();
    Point* temp = new Point[pos];
    for(int i = 0; i < pos; ++i){//for each point i.
        Point ref(array[i]);
        for(int j = 0; j< pos; ++j){
            temp[j] = array[j];
        }
        //now temp is the array of all the points substracting the reference point except the reference point.
        //then we can swap the reference point with the first element, and do the sorting of the rest array.
        //such that temp[0] is always the reference point.
        if(i != 0){//swapping.
            Point pTemp = temp[0];
            temp[0] = temp[i];
            temp[i] = pTemp;
        }
        
        //functor comSlopeTo is used to do the sorting.
        //decleration could be found in pointList.h
        sort(temp + 1, temp+pos, compSlopeTo(ref));
        
        
        int count = 2;//two points form a line, at least two points are collinear at the first place.
        Point firstPoint = temp[1];//the first of the group of points that has the same slope.
        line l;
        
        bool isRefAdded = false;
        //our ultimate goal is to put all the collinear points together as a line type.
        //If we order the collinear points as the increasing order of x position (if points with same x, then we order the point with the increasing order of y position)
        //we can process the line more conveniently. e.g. comparing two lines.
        //and here, we set a bool type is used to prevent multiple insertion of reference point to one line.
        bool isFirstAdded = false;
        //also we need to notice that, when we encountered some point that is no longer collinear with the previous points,
        //the counting would start over, and that point become the first point of another set of collinear point.
        //such that, we need this bool type to indicate whether the counting starting over.
        //then we can insert a new first point to another line.
        
        for(int i = 2; i<pos; ++i){//examing whether the points are collinear. And if so, we put them in a line.
            
            //the examination does not consider the first point and reference point so that we have to discuss the condition of the these two points.
            //for points that are collinear have already been sorted based on their x y position,
            //we also need to put the reference point into the line at a proper position.
            if(!isRefAdded && !isFirstAdded && ref < firstPoint){
                //when the reference point is added in the line, we would not do so again.
                isRefAdded = true;
                isFirstAdded = true;
                l.add(ref);
                l.add(firstPoint);
            }else if(!isFirstAdded){
                isFirstAdded = true;
                l.add(firstPoint);
            }
            
            if(temp[i].slopeTo(ref) == firstPoint.slopeTo(ref)){//if the points are collinear.
                count ++;
                if(ref < temp[i] && !isRefAdded){//insert the reference point to a correct position.
                    isRefAdded = true;
                    l.add(ref);
                    l.add(temp[i]);
                }else{
                    l.add(temp[i]);
                }
            }else if(count <4){
                count =2;//reset the counting.
                firstPoint = temp[i];//if point i fail to has the same slope as previous points', then we use the point i as the first of the group of points that has the same slope to do another examination.
                l.cleanUp();
                isRefAdded = false;
                isFirstAdded = false;
            }else if(count >=4){//print out the points that are collinear.
                if(!isRefAdded){
                    l.add(ref);
                }
                if(!(find(listOfLine.begin(), listOfLine.end(), l) != listOfLine.end())){
                    //if the line already exists, then we would not print it out or add it into the list of lines.
                    //for the comparison, which can be found in line class.
                    //because the points in a line are already sorted based on their x y position,
                    //such that we only need to compare their starting and ending point,
                    //and we would know whether two lines are the same.
                    //each comparison would only take constant time.
                    listOfLine.push_back(l);
                }
                count =2;//reset the counting.
                firstPoint = temp[i];
                l.cleanUp();//clean up the line, so that another round could be carried out.
                isRefAdded = false;
                isFirstAdded = false;
            }
        }
        
    }
    delete [] temp;
}
