#ifndef CART_VECTOR.H
#define CART_VECTOR.H

#include <iostream>
using namespace std;

class Cart_Vector
{
public:
    double x;
    double y;

    Cart_Vector();
    Cart_Vector(double, double);

friend ostream& operator<<(ostream& out, Cart_Vector&);
};

Cart_Vector operator*(Cart_Vector, double);
Cart_Vector operator/(Cart_Vector&, double);

#endif // CartVector
