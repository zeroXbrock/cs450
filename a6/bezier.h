#define NUMCURVES 8
#define NUMPOINTS 30
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

float cubicPoint(float, float, float, float, float);
void RotateX(Point, float, float, float, float);
void RotateY(Point, float, float, float, float);
void RotateZ(Point, float, float, float, float);
void drawBezierCurve(float, float, float, Curve);
void drawEndPoints(Curve *);
void drawPoint(float, float, float);
void setArm(Curve *, float, float, float);
void shiftp0(Curve *, float, float, float);
void shiftp1(Curve *, float, float, float);
void shiftp2(Curve *, float, float, float);
void shiftp3(Curve *, float, float, float);