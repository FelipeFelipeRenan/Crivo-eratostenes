#ifndef CRIVO_H
#define CRIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <stdbool.h>

enum Tag {
   TSEQUENCIAL,
   TPARALELO,
   SPEEDUP
};

bool crivoSeq(int, double*, enum Tag);
bool crivoMP(int, double*, enum Tag);

#endif
