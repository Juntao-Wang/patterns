/**********************************************************************
 *  Pattern Recognition readme.txt template
 **********************************************************************/

Name: WANG Juntao
Login: jwangcc
Hours to complete assignment (optional):


/**********************************************************************
  * compile and run
 **********************************************************************/
% cd Brute_and_Fast
Brute_and_Fast % make
Brute_and_Fast % Brute < input-file-name.txt
Brute_and_Fast % Fast < input-file-name.txt

% cd pointplotter
pointplotter % qmake
pointplotter % make
pointplotter % PointPlotter input-file-name.txt

/**********************************************************************
 *  Step 1.  Explain briefly how you implemented brute force.
 *           What method(s) did you add to the Point data type?
 **********************************************************************/
In brute force, I used nest for loop to search all combinations of four 
points. i.e.
(pseudo code)
for(i from 1 to N)
  for(j from i+1 to N)
    calculate the slope between i and j.
    for(k from j+1 to N)
      calculate the slope between k and j.
      compare this slope with the slope between i and j.
      if the slopes are not the same. this k loop will start another round.
      for(l from k+1 to N)
        calculate the slope between l and k.
        compare this slope with the slope between k and j.
        if the slopes are the same, then we can record these i, j, k, l points.
        if the slopes are not the same, then this l loop will start anoter round.


methods in point class:
int getX(), int getY(), which can get the x, y positions of the point.
int setX(), int setY(), which can reset the x, y positions of the point.
double slopeTo(const Point& p), which can return the slope between this point 
and the other point p.
static methods:
double slope(const Point& p1, const Point& p2), which can return the slope 
between the point p1 and point p2.

operators overload:
operator<, operator==, operator>
we define that, if a point has larger x value, then the point would be considered
as larger. In case points have the same x value, then the point with larger y
value would be considered to be larger. 
operator-, operator+, operator=
arithmetic operators are defined in the normal sense.
operator<<
we can print out the point information more easily.



/**********************************************************************
 *  Step 2.  Explain briefly how you implemented the sorting solution.
 *           Did you sort by angle, slope, or something else?
 *           What method(s) did you add to the Point data type?
 *           What steps did you do to print a minimal representation?
 **********************************************************************/

Given a point p,
1. Think of p as the origin.
2. For each other point q, determine the angle it makes with p.
3. Sort the points according to the angle each makes with p.
4. Check if any 3 (or more) adjacent points in the sorted order have equal 
angles with p. If so, these points, together with p, are collinear.

Remark: 
In the sorting step, I implemented a functor, class compareTo, such that 
this class could store the reference point p_0, and for any other two points,
p_1 and p_2, and functor could give the comparison between their slopes with
respect to reference point. 
And also, concerning the convenience, I also implemented a comparison between 
points, the point with larger x value, would be consider to be larger, if the 
x values are the same, then the point with larger y value would be considered 
to be larger.

methods in point class:
int getX(), int getY(), which can get the x, y positions of the point.
int setX(), int setY(), which can reset the x, y positions of the point.
double slopeTo(const Point& p), which can return the slope between this point 
and the other point p.
static methods:
double slope(const Point& p1, const Point& p2), which can return the slope 
between the point p1 and point p2.

operators overload:
operator<, operator==, operator>
we define that, if a point has larger x value, then the point would be considered
as larger. In case points have the same x value, then the point with larger y
value would be considered to be larger. 
operator-, operator+, operator=
arithmetic operators are defined in the normal sense.
operator<<
we can print out the point information more easily.

To achieve minimal representation:
Firstly, I have defined a line class, so that points could be added into a line type.

Secondly, I have defined a data member listOfLine, which can store the lines.

Thirdly, I have defined a functor, which could sort the points based on their
slopes between reference points and also their relative largeness (see the operators
overloaded in point class). Such that, given a certain list of points and a 
certain reference point, the order of the list after sorting must be the same.
So that this gives the convenience when we add points which are collinear into a line.
Because, for the points they are collinear, they have also been sorted in a increasing
order. Such that when we added the points into a line, the points in that line is 
guaranteed to be in a increasing order. 

Fourthly, based on the third step, we could overload the operator== in line class.
Given two lines, we only need to examine the first point of two lines and last point of 
two lines are the same or not. This boost the comparision speed between lines.
I think this is much better than examining each point is in another existing line or not.

Fifthly, we use find() method to check whether the line exists in the listOfLine, 
if not, then we can add the new line into the listOfLines. 

Remark: 
For N points, the maximum possible number of line is N/4 so that the time
cost by find() is less than the time cost by sort.


/**********************************************************************
 *  Empirical    Fill in the table below with actual running times in
 *  Analysis     seconds when reasonable (say 180 seconds or less).
 *               You can round to the nearest tenth of a second.
 **********************************************************************/

      N       brute      sorting
---------------------------------
     10         0           0
     20         0           0
     40         0           0
     80         0           0
    100         0           0
    150         0           0
    200         0           0
    400         0.1         0.1
   1000         0.5         1.8
   2000         2.2         13.7
   4000         9.5         110.0
  10000         49.4        >180

(remark: these values could fluctuate.)
/**********************************************************************
 *  Estimate how long it would take to solve an instance of size
 *  N = 1,000,000 for each of the two algorithms using your computer.
 **********************************************************************/
Brute:
according to the experiment results, for N = 1000 000, it would take 
around 1.8 * 10^9 sec to 1.8 * 10^12 sec, depending on the input data.
Because the best case of this algorithms is O(N^3), and the worst case is 
O(N^4) time.

Sorting:
according to the experiment results, for N = 1000 000, it would take 
around 4.94 * 10^5 sec. For average case, this algorithm take O(N^2Log N) time.



/**********************************************************************
 *  Theoretical   Give the worst-case running time of your programs
 *  Analysis      as a function of N. Justify your answer briefly.
 **********************************************************************/
Brute:
Totally, we have four nested for loops, such that the worse case is 
O(N^4).

Sorting:
The threshold of this algorithm is the sorting. For each point operation,
we firstly copy the list of nodes to a temp list, which costs O(N) time.
And then we do the sorting, which costs O(N^2) times in the worst case. After 
sorting, we compare the slopes between adjancent points, and this process 
only runs through the temp list once, so it only cost O(N) times. And we also
applied the find() method, however the maximum number of lines is N/4,
so, find() at most cost O(N). Totally, For N points, it would cost
N * O(N^2) = O(N^3) for the worst case.





/**********************************************************************
 *  Known bugs / limitations. For example, if your program prints
 *  out different representations of the same line segment when there
 *  are 5 or more points on a line segment, indicate that here.
 **********************************************************************/
In brute force method, the program will print out different representations 
of the same line segment when there are 5 or more points on a line segment.
However this would not happen in fast method.

The menu bar is inside the graph, but I think this is not a big deal.


/**********************************************************************
 *  List whatever help (if any) that you received. Be specific with
 *  the names of lab TAs, classmates, or course staff members.
 **********************************************************************/
None.


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
None.



/**********************************************************************
 *  List any other comments here. Feel free to provide any feedback   
 *  on how much you learned from doing the assignment, and whether    
 *  you enjoyed doing it.                                             
 **********************************************************************/
good!