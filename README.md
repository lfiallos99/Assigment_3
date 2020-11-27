# Assigment_3
A continuacion se presenta una guía sobre la forma de instalar y ejecutar Assigment_3
## ¿Qué es Assigment_3?
Assigment_3 es un paquete de códigos que permite hallar las soluciones de la ecuación de calor unidimensional mediante el método de Euler Explícito e Implícito. Al ejecutarse este nos escribe un archivo de extensión .dat con los datos presentados en forma de matriz el cual puede ser empleado en un graficador como GNUplot.
## ¿Comó descargo y ejecuto Assigment_3?
Un clon de los archivos de Assigment_3 puede ser descargado desde GitHub a manera de archivo.zip 
## Requesitos Necesarios 
 * make
 * compilador de C
 ## Compilación y Ejecución
 Colocar todos los archivos del paquete de códigos dentro del directorio desde el cual se van a compilar y ejecutar usando C. En el paquete se encuentra un 'Makefile' el cual trae todas las instrucciones para compilar el programa principal. Para esto solo ejecutamos el comando:
 ```
$ make
```
asegurandonos de que no exista más de un 'Makefile' en nuestro directorio. Posteriormente, para la ejecución del programa ejecutamos el comando:
 ```
$ ./SOLHEAD.exe
```
Al finalizar la ejecución del programa este creará 2 archivos datos_explicito.dat y datos_implicito.dat dentro de nuestro directorio el cual posee las coordenadas distribuidas a manera de matriz de la solución de la ecuación de calor. Dichos datos podrán ser empleados en algun graficador que nos permita cargar los datos.
## Graficando la solución con GNUplot
Los datos obtenidos tras la ejecución del programa pueden ser facilmente graficados empleando GNUplot. Para esto, corremos el programa de graficación y ubicamos los archivos de datos dentro del directorio desde que se obtendrá la información. Finalmente, podemos realizar una gráfica simple de la información ejecutando los siguientes comandos en orden dentro del ambiente de GNUplot
 ```
gnuplot> set xlabel 'Espacio'
gnuplot> set ylabel 'Tiempo'
gnuplot> set zlabel 'Temperatura'
gnuplot> set title 'Metodo Implicito'
gnuplot> splot 'datos_implicito.dat' nonuniform matrix using 1:2:3
```
Al terminar de ejecutar estos comandos se mostrará en pantalla una gráfica de la solución de la ecuación de calor obtenida por el método de Euler implícito. Tambien podemos obtener una gráfica de la solución obtenida mediante el método de Euler explícito ejecutando los comandos a continuación
 ```
gnuplot> set xlabel 'Espacio'
gnuplot> set ylabel 'Tiempo'
gnuplot> set zlabel 'Temperatura'
gnuplot> set title 'Metodo Explicito'
gnuplot> splot 'datos_explicito.dat' nonuniform matrix using 1:2:3
```
