#define NUMCURVES 4
#define NUMPOINTS 20
#include <math.h>

struct Point
{
        float x0, y0, z0;       // initial coordinates
        float x,  y,  z;        // animated coordinates
};

struct Curve
{
        float r, g, b;
        Point p0, p1, p2, p3;
};

float cubicPoint(float t, float p0, float p1, float p2, float p3);
void RotateX(Point *p, float deg, float xc, float yc, float zc);
void RotateY(Point *p, float deg, float xc, float yc, float zc);
void RotateZ(Point *p, float deg, float xc, float yc, float zc);
void drawBezierCurve(float r, float g, float b, Curve c);
void setArm(Curve *c, float dx, float dy, float dz);