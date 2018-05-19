#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include "transferFunction.h"
#include <assert.h>

void SetZeros(transferFunc * self, double complex * zeros){
    assert(self->_zeros==NULL&&"零点已经设置");
    self->_zeros = zeros;
}
void SetPolars(transferFunc * self, double complex *polars){

    assert(self->_polars==NULL&&"零点已经设置");
    self->_polars=polars;
}

double AFFunc(transferFunc *self, double w)
{
    assert(self->_polars!=NULL&&"极点未设置");
    assert(self->_zeros!=NULL&&"零点未设置");
    int zN = (int)(self->_zeros[0]);
    int pN = (int)(self->_polars[0]);
    double complex cw = 0 + w*I;
    double sum_N=1,sum_M=1;
    for (int i = 1;i <= zN  ; i ++){
        sum_N *=cabs(self->_zeros[i]-cw);
        printf("zeros: %lf\n",cabs(self->_zeros[i]-cw));
    }
    for (int i = 1;i <= pN  ; i ++){
        sum_M *=cabs(self->_polars[i]-cw);
        printf("polars: %lf\n",cabs(self->_polars[i]-cw));
    }
    return  sum_N/sum_M;
}


double PFFunc(transferFunc *self, double w)
{
    assert(self->_polars!=NULL&&"极点未设置");
    assert(self->_zeros!=NULL&&"零点未设置");
    int zN = (int)(self->_zeros[0]);
    int pN = (int)(self->_polars[0]);
    double complex cw = 0 + w*I;
    double sum_N=0,sum_M=0;
    for (int i = 1;i <= zN  ; i ++)
        sum_N +=carg(cw-self->_zeros[i]);
    for (int i = 1;i <= pN  ; i ++)
        sum_M +=carg(cw-self->_polars[i]);
    return  sum_N-sum_M;
}

transferFunc* transferFunc_construct(){
    transferFunc * self = (transferFunc *)malloc(sizeof(transferFunc));
    self->_zeros = NULL;
    self ->_polars  =NULL;
    self->AFfunc = &AFFunc;
    self->PFfunc = &PFFunc;
    self->setPolars = &SetPolars;
    self->setZeros = &SetZeros;
}
