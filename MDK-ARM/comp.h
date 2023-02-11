#ifndef __COMP_H__
#define __COMP_H__
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<math.h>
#include "calc.h"

typedef struct {

		double real;
		double imag;
}Comp;

Comp add(Comp c1,Comp c2);
Comp minus(Comp c1,Comp c2);
Comp mul(Comp c1,Comp c2);
Comp divi(Comp c1,Comp c2);
void calc_work();
Comp comp_calc(const char str[]);



#endif