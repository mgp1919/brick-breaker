#ifndef GAME_H
#define GAME_H

#include "gba.h"

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


#endif
