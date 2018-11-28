#include "blockstate.h"

#define NUM_BOXES 3


int pick = 0;           // tracks which node will "mine the block"

enum State
{
    idle = 0,
    receiving = 1,
    mining = 2,
    committing = 3
};

char* stateName(State s){
    static char *c = "";
    switch (s)
    {
        case idle:
            c = "IDLE";
            break;
        case receiving:
            c = "RECEIVING TX";
            break;
        case mining:
            c = "MINING";
            break;
        case committing:
            c = "COMMITTING";
            break;
    }
    return c;
}

float *wireColorByState(State s)
{
    static float c[3] = {1., 1., 1.};
    switch (s)
    {
    case idle:
        c[0] = 0.;
        c[1] = 0.2;
        c[2] = 0.8;
        break;
    case receiving:
        c[0] = 0.8;
        c[1] = 0.75;
        c[2] = 0.1;
        break;
    case mining:
        c[0] = 0.7;
        c[1] = 0.4;
        c[2] = 0.;
        break;
    case committing:
        c[0] = 0.0;
        c[1] = 0.8;
        c[2] = 0.3;
        break;
    }
    return c;
}

float **boxColorsByState(State s)
{
    // init 2d array (frickin C man... shoulda used vectors)
    static float **box_colors = 0;
    box_colors = new float *[NUM_BOXES];
    for (int i = 0; i < 3; i++)
    {
        box_colors[i] = new float[3]; //rgb
    }

    switch (s)
    {
    case idle:
    case receiving:
        // all boxes same color
        for (int i = 0; i < NUM_BOXES; i++)
        {
            box_colors[i][0] = 0.;
            box_colors[i][1] = 1.;
            box_colors[i][2] = 0.5;
        }
        break;
    case mining:
        // all boxes same color
        float *c;
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
        for (int i = 1; i < 3; i++)
        {
            box_colors[(pick + i) % 3][0] = 0.5;
            box_colors[(pick + i) % 3][1] = 0.0;
            box_colors[(pick + i) % 3][2] = 0.6;
        }
        break;
    default:
        break;
    }

    return box_colors;
}


int len(const char* str){
    int i = 0;
    while (str[i]){
        i++;
    }
    return i;
}