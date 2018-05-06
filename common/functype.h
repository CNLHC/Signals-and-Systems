
#ifndef FUNCTYPE_H_
#define FUNCTYPE_H_

#define RealFuncSV(name) double(*name)(double)

#define DisFuncSV(name)  double(*name)(int)

#define DisFuncSVN(name) int(*name)(int)

#define CanvasMapFuncSVN(name) int(*name)(double)

double s_heviside(double x);
double s_slope(double x);

#endif