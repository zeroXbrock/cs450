#include "display.h"
#include "bezier.cpp"
#include "glslprogram.h"
#include <stdlib.h>
#include <stdio.h>


/* non-constant variables */
float *wire_color[3];               // list to hold wire color vectors
State STATE;
Curve CurvesStatic[NUMCURVES];      // if you are creating a pattern of other curves
Curve Stem;                         // if you are not
int lastPick = 0;                   // hold a copy of the pick to compare

GLSLProgram *PatternA;
GLSLProgram *PatternB;
float White[] = {1., 1., 1., 1.};

bool initShaderModule(){
    PatternA = new GLSLProgram();
    PatternB = new GLSLProgram();
    bool valid = PatternA->Create("pattern.vert", "pattern.frag");
    bool valid2 = PatternB->Create("pattern.vert", "pattern.2.frag");
    if (!valid || !valid2)
    {
        fprintf(stderr, "Shader cannot be created!\n");
        return false;
    }
    else
    {
        fprintf(stderr, "Shader created.\n");
    }
    PatternA->SetVerbose(false);
    PatternB->SetVerbose(false);
    return true;
}


// display function for my stuff
void myDisplay(int doAnimate, void (*Animate)(), float dTime, bool DebugOn = false){
    // control animation w/ KB
    if (doAnimate)
        glutIdleFunc(Animate);
    else
        glutIdleFunc(NULL);

    // control state based on time
    if (dTime < 0.35){
        STATE = idle;
    }
    else if (dTime < 0.5){
        STATE = receiving;
    }
    else if (dTime < 0.85){
        STATE = mining;
    }
    else if (dTime < 1.){
        STATE = committing;
        // change lastPick to (later) shift committing node
        if (pick == lastPick)
            lastPick++;
    }

    // set color of all wires
    for (int i = 0; i < 3; i++)
    {
        wire_color[i] = wireColorByState(STATE);
        /* NOTE: all wires inherently have the same color */
    }

    // shift committing node if not already done
    if (STATE == idle && lastPick != pick){
        pick = (pick + 1) % 3;
        lastPick = pick;
    }

    // draw boxes
    drawBoxes();
	
    // text and sphere can have their own matrixes
    glPushMatrix();
        SetMaterial(1.0, 1.0, 1.0, 1.);
        // draw text to show the state
        const char *wc = stateName(STATE);
        float dx = len(stateName(STATE)) * -0.08;
        float dy = -3.5;
        float dz = 1.;
        glTranslatef(dx, dy, dz);
        DoStrokeString(0., 2., 0., 0.4, stateName(STATE));
        glTranslatef(-dx, -dy, -dz);

        SetMaterial(0.2, 0.6, 1.0, 1.);
        // represent the internet as a sphere
        glTranslatef(0., -1., 2.);
        glutSolidSphere(0.3, 20, 20);
        glTranslatef(0., 1., -2.);
    glPopMatrix();
}


void drawBoxes(){
    glTranslatef(-3., 0., 0.);
    float bm[4];

    for (int i = 0; i < 3; i++)
    {
        glTranslatef(1.5, 0., 0.);
        glPushMatrix();
            
            if (i == pick && STATE == committing){
                PatternB->Use();
                bm[0] =  1.;
                bm[1] =  1.;
                bm[2] =  1.;
                bm[3] =  1.;
            }
            else{
                PatternA->Use();
                bm[0] =  0.1;
                bm[1] =  0.1;
                bm[2] =  0.1;
                bm[3] =  1.0;
            }
            
            // draw node
            glutSolidCube(1.);

            // draw blocks on chain for each node
            // stop using pattern for blocks
            PatternA->Use(0);
            PatternB->Use(0);

            SetMaterial(bm[0], bm[1], bm[2], bm[3]);
            drawBlocks();
        glPopMatrix();
    }
    glTranslatef(-1.5, 0., 0.);
}


void drawStars(){
    for (int i = 0; i < 100; i++){
        float d = (float)((rand() % 1000) - 500) / 100.0 + 2;
        float e = (float)((rand() % 1000) - 500) / 100.0 + 2;
        float f = (float)((rand() % 1000) - 500) / 100.0 + 2;

        glColor3f(d/5., e/5., f/5.);
        glTranslatef(d, e, f);
        glutSolidSphere(0.01, 20, 10);
        glTranslatef(-d, -e, -f);
    }
}

void drawBlocks(){
    // position above node preemptively (looped translate will move it more +Y)
    glTranslatef(0., 0.6, 0.);

    // draw proper number of blocks
    for (int i = 0; i < pick+1; i++){
        glTranslatef(0., 0.6, 0.);
        glutSolidCube(0.5);
    }
    glTranslatef(0., -1.2 - (0.6 * pick), 0.);
}


// draw wires connecting nodes to sphere
void drawWires(){
    placeLeg(&CurvesStatic[1], 0., -1., 2., 0., -0.5, 0.);
    drawEazierCurve(wire_color[1], CurvesStatic[1]);

    placeLeg(&CurvesStatic[0], 0., -1., 2., -1.5, -0.5, 0.);
    drawEazierCurve(wire_color[0], CurvesStatic[0]);

    placeLeg(&CurvesStatic[2], 0., -1., 2., 1.5, -0.5, 0.);
    drawEazierCurve(wire_color[2], CurvesStatic[2]);
}


// use glut to display a string of characters using a raster font:
void DoRasterString(float x, float y, float z, char *s)
{
    glRasterPos3f((GLfloat)x, (GLfloat)y, (GLfloat)z);

    char c; // one character to print
    for (; (c = *s) != '\0'; s++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}


// use glut to display a string of characters using a stroke font:
void DoStrokeString(float x, float y, float z, float ht, char *s)
{
    glPushMatrix();
    glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);
    float sf = ht / (119.05f + 33.33f);
    glScalef((GLfloat)sf, (GLfloat)sf, (GLfloat)sf);
    char c; // one character to print
    for (; (c = *s) != '\0'; s++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    }
    glPopMatrix();
}

/// SHADER MATH =======================

float Dot(float v1[3], float v2[3])
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void Cross(float v1[3], float v2[3], float vout[3])
{
    float tmp[3];
    tmp[0] = v1[1] * v2[2] - v2[1] * v1[2];
    tmp[1] = v2[0] * v1[2] - v1[0] * v2[2];
    tmp[2] = v1[0] * v2[1] - v2[0] * v1[1];
    vout[0] = tmp[0];
    vout[1] = tmp[1];
    vout[2] = tmp[2];
}

float Unit(float vin[3], float vout[3])
{
    float dist = vin[0] * vin[0] + vin[1] * vin[1] + vin[2] * vin[2];
    if (dist > 0.0)
    {
        dist = sqrt(dist);
        vout[0] = vin[0] / dist;
        vout[1] = vin[1] / dist;
        vout[2] = vin[2] / dist;
    }
    else
    {
        vout[0] = vin[0];
        vout[1] = vin[1];
        vout[2] = vin[2];
    }
    return dist;
}

// utility to create an array from 3 separate values:
float *
Array3(float a, float b, float c)
{
    static float array[4];
    array[0] = a;
    array[1] = b;
    array[2] = c;
    array[3] = 1.;
    return array;
}

// utility to create an array from a multiplier and an array:
float *
MulArray3(float factor, float array0[3])
{
    static float array[4];
    array[0] = factor * array0[0];
    array[1] = factor * array0[1];
    array[2] = factor * array0[2];
    array[3] = 1.;
    return array;
}

// sets current material parameters
void SetMaterial(float r, float g, float b, float shininess)
{
    glMaterialfv(GL_BACK, GL_EMISSION, Array3(0., 0., 0.));
    glMaterialfv(GL_BACK, GL_AMBIENT, MulArray3(.4f, White));
    glMaterialfv(GL_BACK, GL_DIFFUSE, MulArray3(1., White));
    glMaterialfv(GL_BACK, GL_SPECULAR, Array3(0., 0., 0.));
    glMaterialf(GL_BACK, GL_SHININESS, 2.f);
    glMaterialfv(GL_FRONT, GL_EMISSION, Array3(0., 0., 0.));
    glMaterialfv(GL_FRONT, GL_AMBIENT, Array3(r, g, b));
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Array3(r, g, b));
    glMaterialfv(GL_FRONT, GL_SPECULAR, MulArray3(.8f, White));
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

// get some lamp
void SetPointLight(int ilight, float x, float y, float z, float r, float g, float b)
{
    glLightfv(ilight, GL_POSITION, Array3(x, y, z));
    glLightfv(ilight, GL_AMBIENT, Array3(0., 0., 0.));
    glLightfv(ilight, GL_DIFFUSE, Array3(r, g, b));
    glLightfv(ilight, GL_SPECULAR, Array3(r, g, b));
    glLightf(ilight, GL_CONSTANT_ATTENUATION, 1.);
    glLightf(ilight, GL_LINEAR_ATTENUATION, 0.5);
    glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.);
    glEnable(ilight);
}