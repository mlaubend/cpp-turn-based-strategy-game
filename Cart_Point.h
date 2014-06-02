#ifndef CART_POINT.H
#define CART_POINT.H

#include <iostream>
#include "Cart_Vector.h"
using namespace std;

class Cart_Point
{
public:
    double x;
    double y;

    Cart_Point();
    Cart_Point(double, double);
    Cart_Point add(Cart_Point, Cart_Vector);

friend ostream& operator<<(ostream& out, Cart_Point& point);
};

double cart_distance(Cart_Point, Cart_Point);
Cart_Point operator+(Cart_Point, Cart_Vector);
Cart_Vector operator-(Cart_Point, Cart_Point);
#endif // Cart_Point
