#include <math.h>

unsigned char isRightTriangle(double ax, double ay, double bx, double by, double cx, double cy)
{
    double d1 = pow(ax - bx, 2) + pow(ay - by, 2);
    double d2 = pow(ax - cx, 2) + pow(ay - cy, 2);
    double d3 = pow(bx - cx, 2) + pow(by - cy, 2);

    return d1 + d2 == d3 || d1 + d3 == d2 || d2 + d3 == d1;
}
