#include "bezier.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "GLUT/glut.h"


//  Curve Curves[NUMCURVES]; // if you are creating a pattern of curves
//  Curve Stem;				// if you are not


float cubicPoint(float t, float p0, float p1, float p2, float p3){
    return  powf((1. - t), 3.) * p0
            + 3 * t * powf((1. - t), 2.) * p1
            + 3 * powf(t, 2.) * (1. - t) * p2
            + powf(t, 3.) * p3;
}

// rotate point <deg> degrees about X axis around a center
void RotateX(Point *p, float deg, float xc, float yc, float zc)
{
    float rad = deg * (M_PI / 180.f); // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;

    float xp = x;
    float yp = y * cos(rad) - z * sin(rad);
    float zp = y * sin(rad) + z * cos(rad);

    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}

// rotate point <deg> degrees about Y axis around a center
void RotateY(Point *p, float deg, float xc, float yc, float zc)
{
    float rad = deg * (M_PI / 180.f); // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;

    float xp = x * cos(rad) + z * sin(rad);
    float yp = y;
    float zp = -x * sin(rad) + z * cos(rad);

    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}

// rotate point <deg> degrees about Z axis around a center
void RotateZ(Point *p, float deg, float xc, float yc, float zc)
{
    float rad = deg * (M_PI / 180.f); // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;

    float xp = x * cos(rad) - y * sin(rad);
    float yp = x * sin(rad) + y * cos(rad);
    float zp = z;

    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}

// draw a bezier curve
void drawBezierCurve(float r, float g, float b, Curve c){
    Point p0 = c.p0;
    Point p1 = c.p1;
    Point p2 = c.p2;
    Point p3 = c.p3;
    
    glLineWidth(3.);
    glColor3f(r, g, b);
    glBegin(GL_LINE_STRIP);
    for (int it = 0; it <= NUMPOINTS; it++)
    {
        float t = (float)it / (float)NUMPOINTS;
        float omt = 1.f - t;
        float x = omt * omt * omt * p0.x + 3.f * t * omt * omt * p1.x + 3.f * t * t * omt * p2.x + t * t * t * p3.x;
        float y = omt * omt * omt * p0.y + 3.f * t * omt * omt * p1.y + 3.f * t * t * omt * p2.y + t * t * t * p3.y;
        float z = omt * omt * omt * p0.z + 3.f * t * omt * omt * p1.z + 3.f * t * t * omt * p2.z + t * t * t * p3.z;
        glVertex3f(x, y, z);
    }
    glEnd();
    glLineWidth(1.);
}