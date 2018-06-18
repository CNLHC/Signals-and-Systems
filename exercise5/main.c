#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "plot.h"
#include "lambda.h"
#include "functype.h"

#define MAX_SERIES_LENGTH 5000
#define PI 3.14159265358979323846
double gSeries[MAX_SERIES_LENGTH];
#define Order_Offset 2
#define DI(x) (x+Order_Offset) //differentice equation index shortcut. e.g when i use y(n-2), actually i want to access zero index.
#define Y(n)(gSeries[DI(n)])


double go(int n){
    return (1.3*Y(n-1)-0.4*Y(n-2));
}
int main()
{
    //设定初值
    Y(-2)=0;
    Y(-1)=0;
    Y(0)=1;
    //迭代求解
    int i=1;
    while(i<=10){
        Y(i)=go(i);
        i++;
    }
    //进行时移。事实上Y(n)目前是右端项为X(n)时的冲击响应。由LTI性质,Y(n-1)为X(n-1)时的冲击响应,记H(n)
    #define H(n) (Y(n-1))
    //计算传递函数
    double complex  G[1000];
    #define  MapZoomIn(x) ((x/1000.0)*2*PI)
    #define MapZoomOut(x) ((int)((x/(2.0*PI))*1000.0))

    for(i=0;i<1000;i++){
        G[i]=0;
        int n=0;
        for (n=0;n<=10;n++)
        G[i]+=H(n)*cexp(-1*I*n*MapZoomIn(i));
    }

    //计算幅频曲线
    Func_RealSV AMP = Lambda(double _(double x){return cabs(G[MapZoomOut(x)]);});
    Func_RealSV Phrase = Lambda(double _(double x){return carg(G[MapZoomOut(x)]);});


    FILE *result,*temp;
    result = fopen("./AMP_Result.csv","w");
    temp = fopen("./.AMP.temp","w");
    cplot *plter=cplot_construct(NULL);
    plter->setCanvas(plter,40,180);
    plter->setBound(plter,0,2*PI,0,9);
    plter->cleanCanvas(plter);
    plter->plotReal(plter,AMP,'x');
    for(double di=0;di<=1.99*PI;di+=0.1*PI)
        fprintf(result,"%.3f %.3f\n",di,AMP(di));
    for(i=0;i<1000;i++)
        fprintf(temp,"%.3f %.3f\n",MapZoomIn(i),AMP(MapZoomIn(i)));
    fclose(result);
    fclose(temp);
    // plter->printToScreen(plter,"幅频曲线");
    printf("\n");

    result = fopen("./PHRASE_Result.csv","w");
    temp = fopen("./.PHRASE.temp","w");
    plter->setBound(plter,0,2*PI,-4,4);
    plter->cleanCanvas(plter);
    plter->plotReal(plter,Phrase,'x');
    for(double di=0;di<=1.99*PI;di+=0.1*PI)
        fprintf(result,"%.3f %.3f\n",di,Phrase(di));
    for(i=0;i<1000;i++)
        fprintf(temp,"%.3f %.3f\n",MapZoomIn(i),Phrase(MapZoomIn(i)));
    // plter->printToScreen(plter,"相频曲线");
    printf("\n");

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    FILE *gnuplotPipe2 = popen("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "set xzeroaxis \n");
    fprintf(gnuplotPipe, "set style data lines \n");
    fprintf(gnuplotPipe, "plot '.AMP.temp' using 1:2 title \"幅频曲线\", \\\n");
    fprintf(gnuplotPipe2, "set xzeroaxis \n");
    fprintf(gnuplotPipe2, "set style data lines \n");
    fprintf(gnuplotPipe2, "plot 'PHRASE_Result.csv' using 1:2 title \"幅频曲线\", \\\n");
}