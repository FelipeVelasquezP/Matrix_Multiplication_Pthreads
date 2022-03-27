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

/*Global variables*/
int N, Nthreads;
double **Ma, **Mb, **Mc;

/**
 * @brief Function that will be sent to each thread, that makes the matrix multiplication.
 * The matrix A divides in slices, in function with the dimension and the number of threads that requires the 
 * user.
 * 
 * Note: the function will be void, and this returns a potential warning. Think in it to improve it
 * @param arg that has the thread id
 */
void *multMM(void *arg){
	int i,j,k,idTh;
	int portionSize, initRow, endRow;
	double sum;
	idTh=*(int *) arg; //Void pointer to integer 
	portionSize=N/Nthreads; //It is determined the portion of matrix A to send to each thread
	initRow=idTh*portionSize; //It is passed the beggining of the row 
	endRow=(idTh+1)*portionSize; //It is passed the end of the row
	for (i = initRow; i < endRow; i++){
		for (j = 0; j < N; ++j){
			sum=0;
			for ( k = 0; k < N; k++){
				sum+=Ma[i][k]*Mb[k][j];
			}
			Mc[i][j]=sum;
		}
	}
}

/*  @breif main(): Main function
*/
int main(int argc, char* argv[]){
    if (argc!=3){
        printf("./MMPosix <matrix size> <# of threads>\n");
        return -1;
    }

    /*Init of global variables*/
    N           = atof(argv[1]);    /* Matrix's size.*/
    Nthreads    = atof(argv[2]);    /* Number of threads.*/
    
    pthread_t *threads=(pthread_t*)malloc(N*sizeof(pthread_t));//Thread reservation
    /*Memory creation and reserce for each matrix*/
    Ma = memReserve(N); 
    Mb = memReserve(N);
    Mc = memReserve(N);
    initMatrix_DoublePointers (Ma, Mb, Mc, N);
    if (N<4){
        printf("Matriz A\n");
        printMatrix_DoublePointers (Ma, N);
        printf("Matriz B\n");
        printMatrix_DoublePointers (Mb, N);
    }
    sampleStart();
    for (int i = 0; i < Nthreads; ++i){
        int *idThread;
        idThread=(int *)malloc(sizeof(int));
        *idThread=i;
        pthread_create(&threads[i],NULL,multMM,(void *)idThread);
    }
    for (int i = 0; i < Nthreads; ++i){
        
        pthread_join(threads[i],NULL);
    }
    sampleEnd();
    free(threads);
    if (N<4){
        printf("Matriz C\n");
        printMatrix_DoublePointers (Mc, N);
    }

    return 0;
}