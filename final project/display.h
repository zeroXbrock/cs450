#ifndef GL
#define GL 1
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include "GLUT/glut.h"
#endif

#ifndef _USE_MATH_DEFINES
    #define _USE_MATH_DEFINES
    #include <math.h>
#endif

#include "blockstate.cpp"


void DoRasterString(float, float, float, char *);
void DoStrokeString(float, float, float, float, char *);
void myDisplay(int, void(*)(), float);
void drawBoxes(State);
void drawWires();
void drawStars();
