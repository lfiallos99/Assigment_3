#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#define pi   3.14159265358979323846  /*definienddo a pi*/
#include "tools.h"

int main(){
	
	int i,j,p,q;
	double t,alpha,lamda,tiempof,xinicial,xfinal;
	/*A continuacion se resolverá por el metodo explicito*/
	double **matriz_de_coeficientes, **matriz_de_resultados;
	double *vector_tiempo;
	double *vector_coordemadas_de_posicion;
	double *vector_frontera;
	/*Seteando las dimensiones*/
	int ncolum, tfilas;
	alpha=1.;
	xinicial=0.0d;
	xfinal=1.0d;
	tiempof=0.01;
	ncolum=100;
	tfilas=50;
	double dx=1./ncolum;
	double dt=tiempof/tfilas;
	lamda=alpha*(dt/(dx*dx));
	/*sacando el vector inicial*/
	vector_coordemadas_de_posicion=generated_vector(ncolum+1);
	vector_frontera=generated_vector(ncolum+1);
	for(i=0; i<ncolum+1;i++ ){
		vector_coordemadas_de_posicion[i]=xinicial+i*dx;
	}
	for(j=0;j<ncolum+1;j++){
		vector_frontera[j]=exp(vector_coordemadas_de_posicion[j]);
	}
	
	/*Generando la matrz*/
	
	matriz_de_resultados=generated_matriz(ncolum+1,tfilas+1);
	for(i=0; i<ncolum+1;i++){
		matriz_de_resultados[0][i]=vector_frontera[i];
	}
	for(i=0;i<tfilas+1;i++){
		matriz_de_resultados[i][0]=0.0d;
		matriz_de_resultados[i][ncolum]=0.0d;
	}
	/*Construyendo la matriz de coeficientes*/
	matriz_de_coeficientes=generated_matriz(ncolum-1,ncolum-1);
	for(i=0; i<ncolum-1;i++){
		for(j=0;j<ncolum-1;j++){
			if(j==i-1){
				matriz_de_coeficientes[i][j]=lamda;
			}else if(j==i){
				matriz_de_coeficientes[i][j]=1-2*lamda;
			}else if (j==i+1){
				matriz_de_coeficientes[i][j]=lamda;
			}else{
				matriz_de_coeficientes[i][j]=0.0d;
			}
		}
	}
	/*Solucion por el metodo explicito*/
	for(i=1;i<tfilas;i++){
		double *temporal=generated_vector(ncolum-1);
		for (j=0; j<ncolum-1;j++){
			temporal[j]=dt*cos(pi*i*dt)*sin(2*pi*vector_coordemadas_de_posicion[j+1]);
		}
		double *temporal2=generated_vector(ncolum-1);
		for (p=0;p<ncolum-1;p++){
			temporal2[p]=matriz_de_resultados[i-1][p+1];
		}
		double *vector_producto=matriz_vector_multiplicated(matriz_de_coeficientes,temporal2, ncolum-1,ncolum-1);
		double *vector_suma=generated_vector(ncolum-1);
		for(j=0;j<ncolum-1;j++){
			vector_suma[j]=vector_producto[j]+temporal[j];
		}
		for(q=0;q<ncolum-1;q++){
			matriz_de_resultados[i][q+1]=vector_suma[q];
		}
		
	}
	double y= exp(vector_coordemadas_de_posicion[4]);
	
	
	
	printf("aver con f %lf \n", matriz_de_resultados[40][56] );
	
	
	
	
	
	
	
	/*a=generated_matriz(2,2);
	b=generated_vector(2);
	a[0][0]=7.000;
	a[0][1]=-6.0000;
	a[1][0]=-8.000;
	a[1][1]=9.000;
	b[0]=3.0000;
	b[1]=-4.0000;
	/*t=funcion_suma(a,b,0,0,1)*/;
	/*c=matriz_vector_multiplicated(a,b,2,2);
	printf("si sale es correcto, %lf ", c[0]);*/
	
	
	
	return 0;
}