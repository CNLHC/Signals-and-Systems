
#include <complex.h>
#include "functype.h"
#ifndef TRANSFER_FUNCTION_H
#define TRANSFER_FUNCTION_H

typedef struct transferFunc transferFunc;

struct transferFunc{
    double complex* _zeros;
    double complex* _polars;
    void (*setZeros)(transferFunc * self, double complex * zeros);
    void (*setPolars)(transferFunc * self, double complex *polars);
    double (*AFfunc) (transferFunc *self, double w);
    double (*PFfunc) (transferFunc *self, double w);
};

transferFunc* transferFunc_construct();


#endif