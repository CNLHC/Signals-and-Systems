#include <stdio.h>
#include <complex.h>
#include <assert.h>
#include <stdlib.h>
#include "calculus.h"
#include "functype.h"
#include "lambda.h"
#include "plot.h"
#include "math.h"
#include "transferFunction.h"


double complex *zpInputModule(int mode)
{
    char s1[] = "零点";
    char s2[] = "极点";
    char *s = s2;
    int N;
    double complex *out = NULL;
    if (mode == 0)
        s = s1;
    printf("请输入%s个数:", s);
    assert(scanf("%d", &N) == 1 && "输入不合法");
    assert(N >= 0 && "请输入一个非负数");
    out = (double complex *)malloc(sizeof(double complex) * (N + 1));

    out[0] = N;
    if (N != 0)
        printf("请输入%s,格式需满足如下正则表达式 (\\d\\+)\\+(\\d\\+j)\n", s);
    while (N > 0)
    {
        double real, ima;
        double complex temp;
        assert(fscanf(stdin, "%lf+%lfj", &real, &ima) == 2 && "输入格式错误");
        out[(int)(creal(out[0])) - N + 1] = real + ima * I;
        N--;
    }
    return out;
}


int main()
{
    double complex a = 1 + 2 * I;
    double complex b = 0;
     double complex * zeros  = zpInputModule(0);
     double complex * polars = zpInputModule(1);
//    double complex * zeros  = (double complex *)malloc(sizeof(double complex)*2);
//    double complex * polars = (double complex *)malloc(sizeof(double complex)*3);
//    zeros[0]=1;
//    zeros[1]=0.3+0*I;
//    polars[0]=2;
//    polars[1]=-0.1+6*I;
//    polars[2]=-0.1-6*I;
    transferFunc * Hobj = transferFunc_construct();


    Hobj ->setZeros(Hobj,zeros);
    Hobj ->setPolars(Hobj,polars);

    cplot *plter=cplot_construct(NULL);
    plter->setCanvas(plter,40,180);

    plter->setBound(plter,-3,3,-2,2);
    for(int i =zeros[0];i>0;i--)
        plter->plotPointWithNote(plter,creal(zeros[i]),cimag(zeros[i]),'0');
    for(int i =polars[0];i>0;i--)
        plter->plotPointWithNote(plter,creal(polars[i]),cimag(polars[i]),'x');
    plter->printToScreen(plter,"零极点图");
    printf("\n");

    //绘制相频曲线
    plter->setBound(plter,0,5,-3.5,3.5);
    plter->cleanCanvas(plter);
    plter->plotReal(plter,Lambda(double _(double x){return Hobj->PFfunc(Hobj,x);}),'+');
    plter->printToScreen(plter,"相频曲线");
    printf("\n");

    //绘制幅频曲线
    plter->setBound(plter,0,5,0,1);
    plter->cleanCanvas(plter);
    plter->plotReal(plter,Lambda(double _(double x){return Hobj->AFfunc(Hobj,x);}),'+');
    plter->plotPointWithNote(plter,0.95,Hobj->AFfunc(Hobj,0.95),'X');
    plter->printToScreen(plter,"幅频曲线");
    printf("\n");

    //输出结果
    FILE *afp= fopen("./AF-result.csv","w");
    FILE *pfp= fopen("./PF-result.csv","w");

    for(double i = 0 ;i<=5;i+=0.1){
        fprintf(pfp,"%.3lf,%.3lf\n",i,Hobj->PFfunc(Hobj,i));
        fprintf(afp,"%.3lf,%.3lf\n",i,Hobj->AFfunc(Hobj,i));
    }
}