#include "blockstate.h"

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


float* wireColorByState(State s){
    static float c[3] = {1., 1., 1.};
    switch(s){
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
            c[1] = 0.7;
            c[1] = 0.4;
            break;
        case committing:
            c[0] = 0.0;
            c[1] = 0.8;
            c[2] = 0.3;
            break;
    }
    return c;
}


int len(const char* str){
    int i = 0;
    while (str[i]){
        i++;
    }
    return i;
}