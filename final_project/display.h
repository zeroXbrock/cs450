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
void drawBoxes();
void drawWires();
void drawBlocks();
void drawStars();
bool initShaderModule();
void SetPointLight(int, float, float, float, float, float, float);
float Dot(float[3], float[3]);
void Cross(float[3], float[3], float[3]);
float Unit(float[3], float[3]);

float *Array3(float, float, float);
float *MulArray3(float, float[3]);
void SetMaterial(float, float, float, float);
