#include "Cart_Vector.h"

//initializes x and y to their defalut values
Cart_Vector::Cart_Vector()
{
    x = 0.0;
    y = 0.0;
}

//overwrites the default x and y values with the new input values
Cart_Vector::Cart_Vector(double inputx, double inputy)
{
    x = inputx;
    y = inputy;
}


//second overloaded function for << operator.  Formats cartesian vectors to the (x,y) format
ostream& operator<<(ostream& out, Cart_Vector& vect)
{
    out << "(" << vect.x << "," << vect.y <<")";
    return out;
}

Cart_Vector operator*(Cart_Vector vect, double d)
{
    Cart_Vector temp;
    temp.x = (vect.x * d);
    temp.y = (vect.y * d);
    return temp;
}

Cart_Vector operator/(Cart_Vector& vect, double d)
{
    vect.x = vect.x / d;
    vect.y = vect.y / d;
    return vect;
}
