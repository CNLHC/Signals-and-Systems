#include "functype.h"
#include <stdlib.h>

#ifndef CALCULUS_H_
#define CALCULUS_H_

#define SIZEOF_PAIR (sizeof(pair));
/*!c++中std::pair的极简实现
    不能用C++, 我也很绝望啊.
 */
typedef struct pair_double_double
{
    double first;
    double second;
} pair;
/*! 计算一元连续实变函数积分
    \param inf 积分下界
    \param sup 积分上界
    \param func 被积函数
    \param step 积分步长
    \return double 积分结果
*/
double integrateRealSV(double inf, double sup,Func_RealSV, double step);

/*!计算两个一元实变函数的卷积的数值解
    \param range1 paor_double_double 类型，指明函数1的范围
    \param range2 paor_double_double 类型，指明函数1的范围
    \param func1 要卷积的第一个函数
    \param func2 要卷积的第二个函数
    \param step 要卷积的部长
    \return 返回一个pair类型的数组表示数值结果。数组的长度由卷积区间和卷积部长确定。数组的0位存储着1-index的长度。(1-index意为着需要realloc 1+x*sizeof(pair)的长度)
    Warning:注意内存管理，返回的pair数组存储在堆上！
 */
pair *convolution(pair range1, pair range2, Func_RealSV func1, Func_RealSV func2, double step);

#endif

