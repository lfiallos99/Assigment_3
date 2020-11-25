#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include "tools.h"

int main(){
	
	int i,j,p,q;
	double t;
	/*A continuacion se resolverá por el metodo explicito*/
	double **a;
	double *b;
	double *c;
	a=generated_matriz(2,2);
	b=generated_vector(2);
	a[0][0]=7.000;
	a[0][1]=-6.0000;
	a[1][0]=-8.000;
	a[1][1]=9.000;
	b[0]=3.0000;
	b[1]=-4.0000;
	/*t=funcion_suma(a,b,0,0,1)*/;
	c=solution_system_of_aquations(a,b,2,50);
	printf("si sale es correcto, %lf ", c[0]);
	
	
	
	return 0;
}