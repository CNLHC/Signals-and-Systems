
#ifndef CANVAS_H_
#define CANVAS_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct canvas canvas;

struct canvas
{
    /*!
     * @param self 对象
     * @param row  行数
     * @param column  列数
     */
    void (*makeCanvas)(canvas *self, int row, int column);
    void (*clearCanvas)(canvas *self);
    int (*hasCanvas)(canvas *self);
    /*!
     * @param self 对象
     * @param row  行数
     * @param column  列数
     * @param mark  显示标记
     *
     */
    void (*setPoint)(canvas *self, int row, int column, char mark);
    void (*setBlankSymbol)(canvas *self, char mark);

    /*!
     * Canvs中表示空白的符号
     */
    char __blankSymbol;
    /*!
     * Canvas对应的行数
     */
    int row;
    /*!
     * Canvas对应的列数
     */
    int column;
    char **canvasHead;
};

canvas *canvas_construct(canvas *self);
#endif