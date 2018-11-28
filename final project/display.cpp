#include "display.h"
#include "bezier.cpp"
#include <stdlib.h>
#include <stdio.h>

#define NUM_BOXES 3

/* non-constant variables */
float *wireColors[3]; // list to hold wire color vectors
State STATE;
Curve CurvesStatic[NUMCURVES]; // if you are creating a pattern of other curves
Curve Stem;                    // if you are not


void initDisplayModule(){
    return;
}


// display function for my stuff
void myDisplay(int doAnimate, void (*Animate)(), float dTime){
    // control animation w/ KB
    if (doAnimate)
        glutIdleFunc(Animate);
    else
        glutIdleFunc(NULL);

    // control wire colors with time
    if (dTime < 0.35)
        STATE = idle;
    else if (dTime < 0.5)
        STATE = receiving;
    else if (dTime < 0.85)
        STATE = mining;
    else if (dTime < 1.)
        STATE = committing;

    for (int i = 0; i < 3; i++)
    {
        wireColors[i] = wireColorByState(STATE);
    }

    // draw boxes
    drawBoxes(STATE, 0);

    // draw text to show the state
    const char *wc = stateName(STATE);
    float dx = len(stateName(STATE)) * -0.08;
    glTranslatef(dx, 0., 0.);
    DoStrokeString(0., 2., 0., 0.4, stateName(STATE));
    glTranslatef(-dx, 0., 0.);

    // represent the internet as a sphere
    glTranslatef(0., -1., 2.);
    glColor3f(0.1, 0.6, 1.);
    glutSolidSphere(0.3, 20, 20);
    glTranslatef(0., 1., -2.);

    // draw node connections
    drawWires();

    // draw some fuckin stars
    drawStars();
}


float** boxColors(State s, int pick){
    // init 2d array (frickin C man... shoulda used vectors)
    static float **box_colors = 0;
    box_colors = new float*[NUM_BOXES];
    for (int i = 0; i < 3; i++){
        box_colors[i] = new float[3]; //rgb
    }

    switch (s)
    {
        case idle:
        case receiving:
            // all boxes same color
            for (int i = 0; i < NUM_BOXES; i++){
                box_colors[i][0] = 0.;
                box_colors[i][1] = 1.;
                box_colors[i][2] = 0.5;
            }
            break;
        case mining:
            // all boxes same color
            float* c;
            c = wireColorByState(s);
            for (int i = 0; i < NUM_BOXES; i++)
            {
                box_colors[i][0] = c[0];
                box_colors[i][1] = c[1];
                box_colors[i][2] = c[2];
            }
            break;
        case committing:
            // one box turns yellow
            box_colors[pick % 3][0] = 0.9;
            box_colors[pick % 3][1] = 0.7;
            box_colors[pick % 3][2] = 0.0;

            // the other two turn purple
            for (int i = 1; i < 3; i++){
                box_colors[(pick + i) % 3][0] = 0.6;
                box_colors[(pick + i) % 3][1] = 0.0;
                box_colors[(pick + i) % 3][2] = 0.7;
            }
            break;
        default:
            break;
    }

    return box_colors;
}


void drawBoxes(State s, int pick=0){
    float** colors;
    colors = boxColors(s, pick);

    glTranslatef(-3., 0., 0.);

    for (int i = 0; i < 3; i++)
    {
        glTranslatef(1.5, 0., 0.);
        glColor3f(colors[i][0], colors[i][1], colors[i][2]);
        glutSolidCube(1.);
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


// draw wires connecting nodes to sphere
void drawWires(){
    placeLeg(&CurvesStatic[1], 0., -1., 2., 0., -0.5, 0.);
    drawEazierCurve(wireColors[1], CurvesStatic[1]);

    placeLeg(&CurvesStatic[0], 0., -1., 2., -1.5, -0.5, 0.);
    drawEazierCurve(wireColors[0], CurvesStatic[0]);

    placeLeg(&CurvesStatic[2], 0., -1., 2., 1.5, -0.5, 0.);
    drawEazierCurve(wireColors[2], CurvesStatic[2]);
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
