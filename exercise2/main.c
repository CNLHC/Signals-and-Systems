#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "plot.h"
#include "lambda.h"
#include "functype.h"

void inputFrequencyDomain();
int main(){
    // inputFrequencyDomain();
    double complex a=1+2*I;
    printf("%lf+%lfi\n",creal( cexp(a)),cimag(cexp(a)));

    
    


    
    

}
void inputFrequencyDomain()
{
    cplot *plter=cplot_construct(NULL);
    plter->setBound(plter,-M_PI,M_PI,0,1.2);
    plter->setCanvas(plter,60,120);
    double (*gate)(double x) =Lambda(double _(double x){return s_heviside(x+0.5*M_PI)-s_heviside(x-0.5*M_PI);});
    plter->plotReal(plter,Lambda(double _(double x){return gate(x)*cos(x);}),'+');
    plter->printToScreen(plter,"Input Signal in Frequency Domain");
}

