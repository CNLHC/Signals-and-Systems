#ifndef PLOT_H_
#define PLOT_H_
#include "canvas.h"
#include "functype.h"
typedef struct cplot cplot;
struct cplot{

    int (*__mapX2Col)(cplot *self,double x);
    int (*__mapY2Row)(cplot *self,double y);
    double (*__mapCol2x)(cplot *self,int col);
    double (*__mapRow2y)(cplot *self,int row);
    double __xInf;
    double __xSup;
    double __yInf;
    double __ySup;
    int (* __isSetBound)(cplot *self);
    int (* __isSetCanvas)(cplot *self);
    int __boundSetFlag;
    int __showAxiesFlag;
    canvas *__Canv;
    void (*plotReal)(cplot * self,RealFuncSV(func),char mark);
    void (*setBound)(cplot * self,double xI,double xS,double yI,double yS);
    void (*setCanvas)(cplot * self,int row, int column);
    void (*printToScreen)(cplot * self,char *title);
};

cplot *cplot_construct(cplot * obj);

#endif