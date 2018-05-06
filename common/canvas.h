
#ifndef CANVAS_H_
#define CANVAS_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct canvas canvas;

struct canvas
{
    void (*makeCanvas)(canvas *self, int row, int column);
    void (*clearCanvas)(canvas *self);
    int (*hasCanvas)(canvas *self);
    void (*setPoint)(canvas *self, int x, int y, char mark);
    void (*setBlankSymbol)(canvas *self, char mark);

    char __blankSymbol;
    int row;
    int column;
    char **canvasHead;
};

canvas *canvas_construct(canvas *self);
#endif