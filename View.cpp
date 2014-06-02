#include "View.h"
#include "Game_Object.h"

using namespace std;

//View constructor.  Initializes the size, scale and origin.
View::View()
{
    size = 11;
    scale = 2;
    Cart_Point O(0,0);
    origin = (O);
 }

//initializes the arrays' with '.'s and provides the scaled axes.
void View::clear()
{
    //fills the array with '.'s
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                if (k % 2 == 0)
                    grid[i][j][k] = '.';
                else
                    grid[i][j][k] = ' ';
            }
        }
    }

}

Cart_Point View::get_origin()
{
    return origin;
}

double View::get_scale()
{
    return scale;
}

bool View::get_subscripts(int &ix, int &iy, Cart_Point location)
{
    ix = (location.x - ((get_origin()).x))/get_scale();
    iy = (location.y - ((get_origin()).y))/get_scale();

    if (ix <= size && iy <= size)
        return true;
    else
    {
        cout << "An object is outside the display" << endl;
        return false;
    }
}

void View::plot(Game_Object* ptr)
{
    int x;
    int y;

    if (get_subscripts(x, y, (*ptr).get_location()) == true)
    {
        if (grid[y][x][0] != '.')
        {
            grid[y][x][0] = '*';
            grid[y][x][1] = ' ';
        }

        else
            (*ptr).drawself(grid[y][x]);
    }
}

void View::draw()
{
    //prints the board onto the screen
    double count = (size - 1) * scale;
    for (int i = size - 1; i >= 0; i--)
    {
        if (i % 2 == 0)
            {
                if (count < 10)
                {
                    cout << count << " ";
                    count -= scale;
                }

                else if (count >= 10 && i < view_maxsize)
                {
                    cout << count;
                    count -= scale;
                }

                else if (i = view_maxsize)
                    cout << view_maxsize;

            }
        else
        {
            cout << "  ";
            count -= scale;
        }

        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                cout << grid[i][j][k] << " ";
            }
        }
    cout << endl;
    }

    char x_axis[1][size][2];
    int counter = 0;
    double counter_10 = 0;
        {
            for (int j = 0; j < size; j++)
            {
                if (j % 2 == 0)
                {
                    if (counter < 10)
                    {
                    x_axis[0][j][0] = '0' + counter * scale;
                    x_axis[0][j][1] = ' ';
                    counter += scale;
                    }


                    if (counter >= 10)// && counter < 20)
                    {
                        x_axis[0][j][0] = '1';
                        x_axis[0][j][1] = '0' + counter_10 * scale;
                        counter_10 += scale;
                        counter += scale;
                    }

                        /*else if (counter = 20)
                        {
                            x_axis[0][j][0] = '2';
                            x_axis[0][j][1] = '0';
                            counter_10 += 1;
                        }*/

                }
                else
                {
                    x_axis[0][j][0] = ' ';
                }
            }
        }

        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < 2; k++)
                cout << " " << x_axis[0][j][k];
        }
        cout << endl;
}




