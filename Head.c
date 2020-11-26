#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#define pi   3.14159265358979323846  /*definienddo a pi*/
#include "tools.h"

int main(){
	
	int i,j,p,q;
	double t,alpha,lamda,tiempof,xinicial,xfinal;
	/*A continuacion se resolverá por el metodo explicito*/
	double **matriz_de_coeficientes, **matriz_de_resultados;
	double *vector_tiempo;
	double *vector_coordemadas_de_posicion, *vector_del_tiempo;
	double *vector_frontera;
	/*Seteando las dimensiones*/
	int ncolum, tfilas;
	alpha=1.;
	xinicial=0.0d;      /*Solo se debe de cambiar aqui, para ver la convergencia*/
	xfinal=1.0d;
	tiempof=0.01;
	ncolum=100;
	tfilas=1000;
	double dx=(xfinal-xinicial)/ncolum;
	double dt=tiempof/tfilas;
	lamda=alpha*(dt/(dx*dx));               // cuando esto es menor a 1/2 converge para el explicito
	/*sacando el vector inicial*/
	vector_coordemadas_de_posicion=generated_vector(ncolum+1);
	vector_frontera=generated_vector(ncolum+1);
	for(i=0; i<ncolum+1;i++ ){
		vector_coordemadas_de_posicion[i]=xinicial+i*dx;
	}
	vector_del_tiempo=generated_vector(tfilas+1);
	for(i=0;i<tfilas+1;i++){
		vector_del_tiempo[i]=i*dt;
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
	for(i=1;i<tfilas+1;i++){
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
	
	/*Resolució por el metodo implicito*/
	double **matriz_implicita_result;
	double **matriz_coeficientes_implicita;
	matriz_implicita_result=generated_matriz(ncolum+1, tfilas+1);
	for(i=0; i<ncolum+1;i++){
		matriz_implicita_result[0][i]=vector_frontera[i];
	}
	for(i=0;i<tfilas+1;i++){
		matriz_implicita_result[i][0]=0.0d;
		matriz_implicita_result[i][ncolum]=0.0d;
	}
	/*Calculando la matriz de coeficientes*/
	matriz_coeficientes_implicita=generated_matriz(ncolum-1,ncolum-1);
	for(i=0; i<ncolum-1;i++){
		for(j=0;j<ncolum-1;j++){
			if(j==i-1){
				matriz_coeficientes_implicita[i][j]=-lamda;
			}else if(j==i){
				matriz_coeficientes_implicita[i][j]=1+2*lamda;
			}else if (j==i+1){
				matriz_coeficientes_implicita[i][j]=-lamda;
			}else{
				matriz_coeficientes_implicita[i][j]=0.0d;
			}
		}
	}
	
	/*Solucion por el metodo de gauss-sissel*/
	int iteraciones=200;
	double TOL=10e-4;
	for(i=1;i<tfilas+1;i++){
		double *temporal=generated_vector(ncolum-1);
		for (j=0; j<ncolum-1;j++){
			temporal[j]=dt*cos(pi*(i+1)*dt)*sin(2*pi*vector_coordemadas_de_posicion[j+1]);
		}
		double *temporal_implicita=generated_vector(ncolum-1);
		for (p=0;p<ncolum-1;p++){
			temporal_implicita[p]=matriz_implicita_result[i-1][p+1];
		}
		double *vector_suma_implicito=generated_vector(ncolum-1);
		for (j=0;j<ncolum-1;j++){
			vector_suma_implicito[j]= temporal_implicita[j]+temporal[j];
		}
		double *temporal2=generated_vector(ncolum-1);
		temporal2=solution_system_of_aquations(matriz_coeficientes_implicita,vector_suma_implicito,ncolum-1, 2000,TOL );
		for(q=0;q<ncolum-1;q++){
			matriz_implicita_result[i][q+1]=temporal2[q];
		}
		
	}
	
	FILE *archivo_explicito;
	archivo_explicito=fopen("datos_explicito.dat", "w");
	FILE *archivo_implicito;
	archivo_implicito=fopen("datos_implicito.dat", "w");
	if(archivo_explicito==NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	if(archivo_implicito==NULL){
		perror("ERROR. There is not enough memory");
		exit(EXIT_FAILURE);
	}
	char  linea [20000];
	sprintf(linea, "%d    ", ncolum+1);
	for(i=0;i<ncolum+1;i++){
		char buffer[100];
		sprintf(buffer,"%lf  ", vector_coordemadas_de_posicion[i]);
		strcat(linea,buffer);
	}
	int len=strlen(linea);
	linea[len-1]='\n';
	fputs(linea,archivo_explicito);
	for(i=0;i<tfilas+1;i++){
		linea[0]='\0';
		char buffer1[100];
		sprintf(buffer1, "%lf  ", vector_del_tiempo[i]);
		strcat(linea, buffer1);
		for(j=0;j<ncolum+1;j++){
			char buffer2[150];
			sprintf(buffer2, "   %lf", matriz_de_resultados[i][j]);
			strcat(linea,buffer2);
		}
		int len2=strlen(linea);
		linea[len2-1]='\n';
		fputs(linea,archivo_explicito);
	}
	
	char  linea2 [20000];
	sprintf(linea2, "%d    ", ncolum+1);
	for(i=0;i<ncolum+1;i++){
		char buffer[100];
		sprintf(buffer,"%lf  ", vector_coordemadas_de_posicion[i]);
		strcat(linea2,buffer);
	}
	int len3=strlen(linea2);
	linea2[len3-1]='\n';
	fputs(linea2,archivo_implicito);
	for(i=0;i<tfilas+1;i++){
		linea2[0]='\0';
		char buffer1[100];
		sprintf(buffer1, "%lf  ", vector_del_tiempo[i]);
		strcat(linea2, buffer1);
		for(j=0;j<ncolum+1;j++){
			char buffer2[150];
			sprintf(buffer2, "   %lf", matriz_implicita_result[i][j]);
			strcat(linea2,buffer2);
		}
		int len4=strlen(linea2);
		linea2[len4-1]='\n';
		fputs(linea2,archivo_implicito);
	}
	
	/*for(i=0;i<tfilas+1;i++){
		for(j=0;j<ncolum+1;j++){
			fprintf(archivo_explicito,"%lf   %lf   %lf \n", vector_coordemadas_de_posicion[i], vector_coordemadas_de_posicion[j], matriz_implicita_result[i][j] );
		}
	}*/
	fclose(archivo_explicito);
	fclose(archivo_implicito);
	
	

	
	double y= exp(vector_coordemadas_de_posicion[4]);
	
	
	
	printf("aver con f %lf \n", TOL );
	
	
	
	
	
	
	
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