/*Fecha: 26/03/2022
* Autor: Luis Felipe Velasquez Puentes
* Subject: Parallel and Distributed Computing.
* Topic: Poxis implemetation (Library)
* Description: Application for matrix multiplication
  with the classical algorithm (rows x columns) using
  global variables. Also, using the following functions:
    1. Creation of double pointer variables for matrices
    2. Memory reserve for double pointer matrices
    3. Init matrix
    4. Function for the matrix's product:
        4.1.1 The matrix A is divide and those portions 
        will be sent to an individual thread
        4.1.2 The matrix's size will be sent in the 
        execution.
    5. Matrix's size always squared (NxN)
    6.  Print matrix with double pointer.
*/


/*Interfaces*/
#include "modulo.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <omp.h>

/*Varaible of high value to reserve memory*/
#define DATA_SZ (1024*1024*64*4)

/*Memory space acordin reserve memory value*/
static double MEM_CHUNK[DATA_SZ];


/*  @breif main(): Main function
*/
int main(int argc, char* argv[]){

    double *Ma,*Mb,*Mc;
    //struct arg_struct args;

    if (argc!=3){
        printf("./MMPosix <matrix size> <# of threads>\n");
        return -1;
    }

    /*Init of global variables*/
    int N           = atof(argv[1]);    /* Matrix's size.*/
    int nthreads    = atof(argv[2]);    /* Number of threads.*/
    
    /*It is validated that the number of threads entered is less than or equal to the 
      number of cores detected by the operating system*/
	if(nthreads > omp_get_max_threads()){
		printf("El número de hilos debe ser <= %d \n",omp_get_max_threads());
		return -1;
	}


    /*Memory creation and reserce for each matrix*/
    Ma = MEM_CHUNK;
    Mb = Ma+N*N;
    Mc = Mb+N*N;
    initMatrix(N,Ma, Mb, Mc);

    /*Matrices are printed*/    
    printMatrix(N,Ma);
    printMatrix(N,Mb);
    

    sampleStart();
    MM1cOMP(nthreads,N,Ma,Mb,Mc);
    sampleEnd();
    
    /*Matrices are printed if N is less than 4*/
    printMatrix(N,Mc);
    

    return EXIT_SUCCESS;
}