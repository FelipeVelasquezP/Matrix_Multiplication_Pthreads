/*Fecha: 26/03/2022
* Autor: Luis Felipe Velasquez Puentes
* Subject: Parallel and Distributed Computing.
* Topic: Construction of the first Benchmark
* Description: Application that allows evaluating the performance
  of a specific aspect of the computer using matrix multiplication
  with the calssical algorithm (rows x columns)
*/

/*Interfaces*/

#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>


/*CONSTANTS*/
struct timespec inicio, fin;

/* -------------------------------------Funciones ------------------------------------*/

/*Varaible of high value to reserve memory*/
#define DATA_SZ (1024*1024*64*3)

/*Memory space acordin reserve memory value*/
static double MEM_CHUNK[DATA_SZ];

int main(int argc, char *argv[]) {
	
	/*Matrix size*/
	int N = (int) atof(argv[1]);
	
	/*Apuntamos los vectores (creacion) a espacio de memoria reservada con dimension NxN */
	double *Ma, *Mb, *Mr;
	Ma = MEM_CHUNK;
	Mb = Ma + N*N;
	Mr = Mb + N*N;
	
	initMatrix(N, Ma, Mb, Mr);
	printMatrix(N, Ma);
	printMatrix(N, Mb);

	sampleStart();
	MM1f(N, Ma, Mb, Mr);
	sampleEnd();
		
   	printMatrix(N, Mr);
	return 0;
}
/*
Compile
    gcc modulo.c -c
    gcc MM1c.c -c
	gcc modulo.o MM1c.o -o MM1c
Execute
	time ./MM1c N--> N : Any number
*/
