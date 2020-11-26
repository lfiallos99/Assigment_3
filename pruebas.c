#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include "tools.h"
double **imprimematriz(double **array);
int main(){
	double **array = (double **)malloc(2*sizeof(double *));
	array[0] = (double *)malloc(2*sizeof(double));
	array[1] = (double *)malloc(2*sizeof(double));
	array[0][0]=1;
	array[0][1]=1;
	array[1][0]=1;
	array[1][1]=1;
	
	double **a,*b;
	double *c;
	double p;
	double d[2][2]={{54,44},{48,152}};
	/*c=imprimematriz(array);*/
	/*float dx=1/100;*/
	a=generated_matriz(2,2);
	b=generated_vector(2);
	a[0][0]=7.000;
	a[0][1]=-6.0000;
	a[1][0]=-8.000;
	a[1][1]=9.000;
	b[0]=3.0000;
	b[1]=-4.0000;
	p=10e-6;
	/*t=funcion_suma(a,b,0,0,1);*/
	c=solution_system_of_aquations(a,b,2,50,p);
	printf("si sale es correcto, %lf ", c[0]);
		
	return 0;
}



double **imprimematriz(double **array){
	static double **array2;
	array2=(double **)malloc(2*sizeof(double *));
	array2[0] = (double *)malloc(2*sizeof(double));
	array2[1] = (double *)malloc(2*sizeof(double));
	array2[0][0]=array[0][0]+1;
	array2[0][1]+=array[0][1]+2;
	array2[1][0]+=array[1][0]+3;
	array2[1][1]+=array[1][1]+4;
	printf("El valor es: %lf ", array[0][0]);
	return array2;
}



