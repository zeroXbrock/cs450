#include "bezier.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "GLUT/glut.h"


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

void drawLine(float x0, float y0, float z0, float x1, float y1, float z1){
    glLineWidth(1.);
    glColor3f(1.,1.,1.);
    glBegin(GL_LINE_STRIP);
        glVertex3f(x0, y0, z0);
        glVertex3f(x1, y1, z1);
    glEnd();
}

// sets baseline arm parameters & allows animation via d<x..z>
void placeArm(Curve *c, float x=0., float y=0., float z=0.){
    Point p0, p1, p2, p3;
    p0.x0 = x;
    p0.y0 = y;
    p0.z0 = z;

    p1.x0 = x + 1.;
    p1.z0 = z + 0.85;
    p1.y0 = y + 0.1;

    p2.x0 = x - 1.;
    p2.z0 = z + 0.85;
    p2.y0 = y + 0.2;

    p3.x0 = x;
    p3.z0 = z;
    p3.y0 = y + 0.3;

    p0.x = p0.x0;
    p0.y = p0.y0;
    p0.z = p0.z0;

    p1.x = p1.x0;
    p1.y = p1.y0;
    p1.z = p1.z0;

    p2.x = p2.x0;
    p2.y = p2.y0;
    p2.z = p2.z0;

    p3.x = p3.x0;
    p3.y = p3.y0;
    p3.z = p3.z0;

    c->p0 = p0;
    c->p1 = p1;
    c->p2 = p2;
    c->p3 = p3;
}

void placeLeg(Curve *c, float x = 0., float y = 0., float z = 0.){
    Point p0, p1, p2, p3;
    p0.x0 = x;
    p0.y0 = y;
    p0.z0 = z;

    p1.x0 = x + 0.1;
    p1.z0 = z;
    p1.y0 = y + 0.3;

    p2.x0 = x + 0.4;
    p2.z0 = z;
    p2.y0 = y + 0.6;

    p3.x0 = x + 0.6;
    p3.z0 = z;
    p3.y0 = y + 0.3;

    p0.x = p0.x0;
    p0.y = p0.y0;
    p0.z = p0.z0;

    p1.x = p1.x0;
    p1.y = p1.y0;
    p1.z = p1.z0;

    p2.x = p2.x0;
    p2.y = p2.y0;
    p2.z = p2.z0;

    p3.x = p3.x0;
    p3.y = p3.y0;
    p3.z = p3.z0;

    c->p0 = p0;
    c->p1 = p1;
    c->p2 = p2;
    c->p3 = p3;
}

    // calls drawPoint() for each ctrl point of the given curve c
    void drawControlPoints(Curve c)
{
    float dx, dy, dz;
    dx = c.p0.x;
    dy = c.p0.y;
    dz = c.p0.z;
    drawPoint(dx, dy, dz);

    dx = c.p1.x;
    dy = c.p1.y;
    dz = c.p1.z;
    drawPoint(dx, dy, dz);

    dx = c.p2.x;
    dy = c.p2.y;
    dz = c.p2.z;
    drawPoint(dx, dy, dz);

    dx = c.p3.x;
    dy = c.p3.y;
    dz = c.p3.z;
    drawPoint(dx, dy, dz);
}

void drawControlLines(Curve c){
    drawLine(c.p0.x, c.p0.y, c.p0.z, c.p1.x, c.p1.y, c.p1.z);
    drawLine(c.p1.x, c.p1.y, c.p1.z, c.p2.x, c.p2.y, c.p2.z);
    drawLine(c.p2.x, c.p2.y, c.p2.z, c.p3.x, c.p3.y, c.p3.z);
}

// draws a small white dot at <x,y,z>
void drawPoint(float x, float y, float z)
{
    // move to position
    glTranslatef(x, y, z);
    // draw a small white sphere
    glColor3f(1., 1., 1.);
    glutSolidSphere(0.02, 20, 20);
    // move back to origin
    glTranslatef(-x, -y, -z);
}

// modifies p0 of curve positioning based on d<x..z>
void shiftp0(Curve *c, float dx, float dy, float dz)
{
    c->p0.x += dx;
    c->p0.y += dy;
    c->p0.z += dz;
}

// modifies p1 of curve positioning based on d<x..z>
void shiftp1(Curve *c, float dx, float dy, float dz)
{
    c->p1.x += dx;
    c->p1.y += dy;
    c->p1.z += dz;
}

// modifies p2 of curve positioning based on d<x..z>
void shiftp2(Curve *c, float dx, float dy, float dz)
{
    c->p2.x += dx;
    c->p2.y += dy;
    c->p2.z += dz;
}

// modifies p3 of curve positioning based on d<x..z>
void shiftp3(Curve *c, float dx, float dy, float dz){
    c->p3.x += dx;
    c->p3.y += dy;
    c->p3.z += dz;
}
