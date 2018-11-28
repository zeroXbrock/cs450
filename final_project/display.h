#ifndef GL
#define GL
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include "GL/glut.h"
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
void drawBlocks();
void drawStars();
bool initShaderModule();