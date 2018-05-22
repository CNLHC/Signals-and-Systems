#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lambda.h"
#include "plot.h"
#include "canvas.h"

int __IsSetBound(cplot *self)
{
    return self->__boundSetFlag;
}
int __IsSetCanvas(cplot *self)
{
    return !(self->__Canv == NULL);
}
int __MapX2Col_Linear(cplot *self, double x)
{
    assert(self->__isSetBound(self) && self->__isSetCanvas(self) && "cplot对象未正确初始化,请确保已经设置Canvas以及显示范围");
    int col = self->__Canv->column;
    double interval = self->__xSup - self->__xInf;
    double coe = interval / col;
    double offset = self->__xInf < 0 ? (0 - self->__xInf) : 0;
    return (x + offset) / coe;
}
int __MapY2Row(cplot *self, double y)
{
    assert(self->__isSetBound(self) && self->__isSetCanvas(self) && "cplot对象未正确初始化,请确保已经设置Canvas以及显示范围");
    int row = self->__Canv->row;
    double interval = self->__ySup - self->__yInf;
    double coe = interval / row;
    double offset = self->__yInf < 0 ? (0 - self->__yInf) : 0;
    return (y + offset) / coe;
}
void SetBound(cplot *self, double xI, double xS, double yI, double yS)
{
    assert(self->__Canv!=NULL&&"对象没有正常初始化:Canvas为空");
    assert(xI <= xS && "x坐标轴边界条件错误");
    assert(xI <= xS && "y坐标轴边界条件错误");
    self->__xInf = xI;
    self->__xSup = xS;
    self->__yInf = yI;
    self->__ySup = yS;
    self->__boundSetFlag = 1;
}
void SetCanvas(cplot *self, int row, int column)
{
    assert(!self->__isSetCanvas(self) && "cplot 尝试设置已经初始化的Canvas");
    self->__Canv = canvas_construct(NULL);
    self->__Canv->makeCanvas(self->__Canv, row, column);
    self->__Canv->clearCanvas(self->__Canv);
}
void PlotReal(cplot *self,Func_RealSV func, char mark)
{
    double step = (self->__xSup - self->__xInf) / (20 * self->__Canv->column);
    double idx;
    for (idx = self->__xInf; idx <= self->__xSup; idx += step)
    {
        int col = self->__mapX2Col(self, idx);
        int row = self->__mapY2Row(self, func(idx));
        self->__Canv->setPoint(self->__Canv, row, col, mark);
    }
}
void PrintToScreen(cplot *self,char *title)
{
    printf("%s\n",title);
    int i, j;
    for (i = self->__Canv->row - 1; i >= 0; i--)
    {
        double y = i * (self->__ySup - self->__yInf) / (self->__Canv->row);
        if (self->__showAxiesFlag)
            printf("%06.2lf->\t", y);
        for (j = 0; j < self->__Canv->column; j++)
        {
            printf("%c", self->__Canv->canvasHead[i][j]);
        }
        printf("\n");
    }
    printf("        \t"); //8个空格, 为"%06.2lf->的长度
    for (j = 0; j < self->__Canv->column+10; j++)
            printf("-");
    printf("\n        \t"); //8个空格, 为"%06.2lf->的长度
    int interval=3 ;
    for (j = 0; j < self->__Canv->column+4+interval; j++)
    {
        if(j%(interval+4)==0)
        {
            double x = self->__xInf + (j * (self->__xSup - self->__xInf) / (self->__Canv->column));
            printf("%04.1lf", x);
            j += 3;
        }
        else 
            printf(" ");
        
    }
}
int PlotPointWithNote(cplot *self, double xI, double yI,char mark){
    assert(self->__Canv!=NULL&&"对象没有正常初始化:Canvas为空");
    char pattern[]="-(%.1lf,%.1lf)";
    if (xI<=self->__xInf||xI>=self->__xSup)return 1;
    if (yI<=self->__yInf||yI>=self->__ySup)return 1;
    int Col=self->__mapX2Col(self,xI);
    int Row=self->__mapY2Row(self,yI);
    canvas *boundCanv = self->__Canv;
    boundCanv->setPoint(boundCanv,Row,Col,mark);
    int tR =Row;
    for (tR;tR<=Row+2;tR++){
        int tc =Col+1;
        char tS[11];
        sprintf(tS,pattern,xI,yI);
        for (int i=0;i<=10;i++){
            boundCanv->setPoint(boundCanv,tR,tc+i,tS[i]);
        }
        return 0;
    }
    return 1;
}
void CleanCanvas(cplot * self){
    self->__Canv->clearCanvas(self->__Canv);
}

cplot *cplot_construct(cplot *obj)
{
    if (obj == NULL)
        obj = (cplot *)malloc(sizeof(cplot));

    obj->__boundSetFlag = 0;
    obj->__showAxiesFlag = 1;

    obj->__Canv = NULL;
    obj->__mapX2Col = &__MapX2Col_Linear;
    obj->__mapY2Row = &__MapY2Row;
    obj->__isSetBound = &__IsSetBound;
    obj->__isSetCanvas = &__IsSetCanvas;

    obj->__xInf = 0;
    obj->__xSup = 0;
    obj->__yInf = 0;
    obj->__ySup = 0;

    obj->plotReal = &PlotReal;
    obj->setBound = &SetBound;
    obj->setCanvas = &SetCanvas;
    obj->printToScreen = &PrintToScreen;
    obj->plotPointWithNote =  &PlotPointWithNote;
    obj->cleanCanvas = &CleanCanvas;


    return obj;
}

