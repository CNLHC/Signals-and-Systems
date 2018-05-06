#include "functype.h"
#include "calculus.h"
#include "lambda.h"

double integrateRealSV(double inf, double sup,Func_RealSV func, double step)
{
    double i = 0;
    double result = 0;
    for (i = inf; i < sup; i += step)
    {
        if (i + step > sup)
            step = sup - i;
        result += (*func)(i)*step;
    }
    return result;
}
pair *convolution(pair range1, pair range2, Func_RealSV func1, Func_RealSV func2, double step)
{
    //确定卷积区间
    double inf = range1.first - (range2.second - range2.first);
    double sup = range1.second + (range2.second - range2.first);
    int outputRange = (sup - inf) / step;
    int gov = 1; //gov用于防止数组越界
    pair *pairList = (pair *)malloc(sizeof(pair) * (outputRange + 1));
    pairList[0].first = (double)outputRange;
    for (double t = inf; t <= sup; t += step)
    {
        if (gov > outputRange)
            break;
        double (*func)(double) =Lambda(double _(double x) { return (*func1)(x) * (*func2)(t - x); });
        pairList[gov].first = t;
        pairList[gov].second =integrateRealSV(inf, sup, func, 0.01);
        gov++;
    }
    return pairList;
}

