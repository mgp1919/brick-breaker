#ifndef GAME_H
#define GAME_H

#include "gba.h"

                    /* TODO: */

            // Create any necessary structs //

#define NUM_BRICKS 15

struct ball {
    int row;
    int col;
    int rd;
    int cd;
    unsigned short color;
    int size;
};

struct brick {
    int row;
    int col;
    unsigned short color;
    int height;
    int length;
};

struct blocker {
    int row;
    int col;
    int rd;
    int cd;
    unsigned short color;
    int height;
    int length;
};

struct state {
    struct ball ball;
    struct blocker blocker;
    struct brick brick[NUM_BRICKS];
} cs, ps;

/*
* For example, for a Snake game, one could be:
*
* typedef struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* } Snake;
*
*
* 
*
*
* Example of a struct to hold state machine data:
* 
* typedef struct state {
*   int currentState;
*   int nextState;
* } State
*
*/

#endif
