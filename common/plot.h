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
    void (*cleanCanvas)(cplot * self);
    /*!
     * 在Canvas上绘制一个一元实变函数的图像
     * @param self 对象
     * @param func double => double 类型的对象
     * @param mark 图中点的标记符号
     */
    void (*plotReal)(cplot * self,Func_RealSV func,char mark);
    /*!
     * 在Canvas上绘制一个点,并将点的坐标标记于图上。
     * @param self 对象
     * @param xI 要绘制点的横坐标
     * @param yI 要绘制点的纵坐标
     * @param mark 点在图中的标记符号
     * @return  绘制正常返回0,如果Canvas空间不够或是点超出边界，返回非0值
     */
    int (*plotPointWithNote)(cplot* self,double xI, double yI,char mark);
    /*!
     * 设置 x轴和 y轴的边界
     * @param self 对象
     * @param xI x轴下界
     * @param xS x轴上界
     * @param yI y轴下界
     * @param yS y轴上界
     */
    void (*setBound)(cplot * self,double xI,double xS,double yI,double yS);
    /*!
     * 设置画布.
     * @param self
     * @param row
     * @param column
     * @warning 对于一个对象, 该函数必须调用且只调用一次
     * @todo 该函数应该私有，并于构造函数中初始化
     */
    void (*setCanvas)(cplot * self,int row, int column);
    /*!
     * 在屏幕上打印当前的图像
     * @param self  对象
     * @param title  图像标题
     */
    void (*printToScreen)(cplot * self,char *title);

};

cplot *cplot_construct(cplot * obj);

#endif