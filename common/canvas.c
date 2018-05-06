#include "canvas.h"
#include "assert.h"

//!为canvas对象分配一块内存，用于存储显示信息。
void MakeCanvas(canvas *self, int row, int column)
{
    assert(!(self->hasCanvas(self)) && ("尝试为非空对象分配内存"));
    int idx = 0;
    char **t;
    t = (char **)malloc(sizeof(char *) * row);
    for (idx = 0; idx < row; idx++)
        t[idx] = (char *)malloc(sizeof(char) * column);
    self->canvasHead = t;
    self->row = row;
    self->column = column;
    return;
}
//!返回当前对象是否有画布
int HasCanvas(canvas *self)
{
    return (self->canvasHead == NULL) ? 0 : 1;
}
//!清空当前画布
void ClearCanvas(canvas *self)
{
    assert(self->hasCanvas(self) && ("尝试清除尚未分配画布内存对象的画布"));
    int i, j;
    for (i = 0; i < self->row; i++)
        for (j = 0; j < self->column; j++)
            self->canvasHead[i][j] = self->__blankSymbol;
}
//设置点
void SetPoint(canvas *self, int x, int y, char mark)
{
    if (x > self->column - 1 || y > self->row- 1 || x<0 || y<0)
        return;
    self->canvasHead[y][x] = mark;
}
//设置空白标识符
void SetBlankSymbol(canvas *self, char mark)
{
    int i, j;
    for (i = 0; i < self->row; i++)
        for (j = 0; j < self->column; j++)
            if (self->canvasHead[i][j] == self->__blankSymbol)
                self->canvasHead[i][j] = mark;
    self->__blankSymbol = mark;
}
//!构造函数
canvas *canvas_construct(canvas *self)
{
    if (self == NULL)
        self = (canvas *)malloc(sizeof(canvas));
    self->row = -1;
    self->column = -1;
    self->canvasHead = NULL;
    self->__blankSymbol = ' ';
    self->hasCanvas = &HasCanvas;
    self->clearCanvas = &ClearCanvas;
    self->makeCanvas = &MakeCanvas;
    self->setPoint = &SetPoint;
    self->setBlankSymbol = &SetBlankSymbol;
    return self;
}
