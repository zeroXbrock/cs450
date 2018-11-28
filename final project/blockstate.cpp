#include "blockstate.h"

enum state
{
    idle = 0,
    received = 1,
    mining = 2,
    committing = 3
};

char* stateName(state s){
    static char *c = "";
    switch (s)
    {
        case idle:
            c = "IDLE";
            break;
        case received:
            c = "TX RECEIVED";
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


float* wireColorByState(state s){
    static float c[3] = {1., 1., 1.};
    switch(s){
        case idle:
            c[0] = 0.;
            c[1] = 0.2;
            c[2] = 0.8;
            break;
        case received:
            c[0] = 0.5;
            c[1] = 0.5;
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