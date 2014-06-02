#ifndef VIEW
#define VIEW

#include "Cart_Point.h"
#include "Game_Object.h"
#include "Cart_Point.h"

const int view_maxsize = 20;

class View
{
public:
    View();
    void clear();
    void plot(Game_Object*);
    void draw();
    Cart_Point get_origin();
    double get_scale();

private:
    int size;
    double scale;
    Cart_Point origin;
    char grid[view_maxsize][view_maxsize][2];
    bool get_subscripts(int&, int&, Cart_Point);
};
#endif // VIEW
