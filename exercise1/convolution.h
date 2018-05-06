
#include <stdlib.h>
#include <stdio.h>

/*!c++中std::pair的极简实现
    不能用C++, 我也很绝望啊.
 */
typedef struct pair_double_double
{
    double first;
    double second;
} pair;
pair *convolution(pair range1, pair range2, double (*func1)(double), double (*func2)(double), double step);
pair *animationConvolution(pair range1, pair range2, double (*func1)(double), double (*func2)(double), double step,FILE *pipe);
double integrate(double inf, double sup, double (*func)(double), double step);
double heviside(double x);
FILE *bufFunc(double inf, double sup, double step, double (*func)(double), char *funcname, FILE *buffer);
