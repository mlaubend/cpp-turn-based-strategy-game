#include "Cart_Point.h"
#include "Cart_Vector.h"
#include <cmath>
#include <iostream>
using namespace std;

    double x;
    double y;

    //initializes x and y to their default conditions
Cart_Point::Cart_Point()
{
    x = 0.0;
    y = 0.0;
}

//overwrites the default x and y values with the new input values
Cart_Point::Cart_Point(double inputx, double inputy)
{
    x = inputx;
    y = inputy;
}


//first overloaded function for << operator.  Formats cartesian points to the (x,y) format
ostream& operator<<(ostream& out, Cart_Point& point)
{
    out << "(" << point.x << "," << point.y << ")";
    return out;
}

Cart_Point operator+(Cart_Point point, Cart_Vector vect)
{
    return point.add(point, vect);
}

//adds a cartesian point and vector together.  Must assign the sum to a new variable in order to cout
Cart_Point Cart_Point::add(Cart_Point point, Cart_Vector vect)
{
    Cart_Point temp;
    temp.x = point.x + vect.x;
    temp.y = point.y + vect.y;

    return temp;
}

//subtraction operator.  Must assign to a new variable in order to cout.
Cart_Vector operator-(Cart_Point point1, Cart_Point point2)
{
    Cart_Vector vect;
    vect.x = point1.x - point2.x;
    vect.y = point1.y - point2.y;
    return vect;
}

//function that returns the distance between 2 cartesian points
double cart_distance(Cart_Point p1, Cart_Point p2)
{
    double a = (p2.x - p1.x);
    double b = (p2.y - p1.y);
    return sqrt(a*a + b*b);
}
