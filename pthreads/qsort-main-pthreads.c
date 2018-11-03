/**********************************************************************
 *
 * qsort-main-pthreads.c -- Sequential and Parallel implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Further edits
 * Charalampos Papadiakos <charaldp@auth.gr>
 * Time-stamp: <2018-11-4>
 *
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "qsort-pthreads.h"
#include <assert.h>
#include <pthread.h>
#include "qsort-sequential.h"

int rep;
int threadCounter,userDefinedThreads;
pthread_mutex_t mutex;

typedef struct { int *a, n;
} sortarg;

/* local function declarations */
int  test( int *a, int n);
void copy( int *a, int *b, int n);
void init( int *a, int n);
void print(int *a, int n);
int cmpfunc (const void * a, const void * b);

/* --- Entry POINT --- */
int main(int argc, char **argv) {
  /* variables to hold execution time */
  struct timeval startwtime, endwtime;
  double qsort_time ,seq_time, par_time,mean_qsort ,mean_seq ,mean_par;
  int n_it,n,n1,n2,thr_it,thr1,thr2,k,meanSize, pass;
  int *a_qsort,*a_seq,*a_par;
  FILE *f ;
  /* parse input */
  if (argc != 3 && argc != 5) {
    printf("Usage: %s q p\n  where n=2^q is problem size (power of two) and 2^p is the number of threads\n", argv[0]);
    printf("Altrnative Usage: %s q1 q2 p1 p2\n  where n=2^qi is problem size (power of two) and 2^pi is the number of threads in order to create a excecution time grid\n", argv[0]);
    exit(1);
  }
  else if(argc == 3){
    n1 = atoi(argv[1]);;
    n2 = n1;
    thr1 = atoi(argv[2]);;
    thr2 = thr1;
    meanSize = 1;
    printf("Excecuting singular sorting using n = 2^%d, nThreads = 2^%d...\n",n1,thr1);
  }
  else if(argc == 5){
    n1 = atoi(argv[1]);
    n2 = atoi(argv[2]);
    thr1 = atoi(argv[3]);
    thr2 = atoi(argv[4]);
    printf("File Mode: Writing time grid (n1:n2)x(thr1:thr2) = (%d:%d)x(%d:%d) to file...\n",n1,n2,thr1,thr2);
    f = fopen("pthreads_data.csv", "w");
    meanSize = 3;
    if (f == NULL){
      printf("Error opening file!\n");
      exit(1);
    }
  }


  for(n_it = n1;n_it < n2+1;n_it++){
    for(thr_it = thr1;thr_it < thr2+1;thr_it++){
      mean_qsort = 0;
      mean_seq = 0;
      mean_par = 0;
      /* Using a thrird loop to create an average time value using 3 tests */
      for(k=0;k<meanSize;k++){
        /* initiate vector of random integerts */
        n = 1 << n_it;
        userDefinedThreads = 1 << thr_it;
        a_qsort = (int *) malloc(n * sizeof(int));
        a_seq = (int *) malloc(n * sizeof(int));
        a_par = (int *) malloc(n * sizeof(int));
        /* initialize vector */

        init(a_qsort, n);
        /*
        * Create a copy of the vector intended for serial sorting so that 
        * the same problem will be solved in parallel sorting
        */
        copy(a_seq, a_qsort, n);
        /* print vector */
        //print(a_seq, n);

        /* sort elements in original order */
        gettimeofday (&startwtime, NULL);
        qsort(a_qsort,n, sizeof(int), cmpfunc);
        gettimeofday (&endwtime, NULL);

        /* get time in seconds */
        qsort_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                            + endwtime.tv_sec - startwtime.tv_sec);

        /* validate result */
        pass = test(a_qsort, n);
        if(argc == 3){
          printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
        }
        assert( pass != 0 );
        
          /* print sorted vector */
        //print(a_seq, n);
        
        /* print execution time */
        if(argc == 3){
          printf("stdlib qsort wall clock time: %f sec\n", qsort_time);
        }
        /*
        * Create a copy of the vector intended for serial sorting so that 
        * the same problem will be solved in parallel sorting
        */
        copy(a_par, a_seq, n);
        /* print vector */
        //print(a_seq, n);

        /* sort elements in original order */
        gettimeofday (&startwtime, NULL);
        qsort_seq(a_seq,n);
        gettimeofday (&endwtime, NULL);

        /* get time in seconds */
        seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                            + endwtime.tv_sec - startwtime.tv_sec);

        /* validate result */
        pass = test(a_seq, n);
        if(argc == 3){
          printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
        }
        assert( pass != 0 );
        
          /* print sorted vector */
        //print(a_seq, n);
        
        /* print execution time */
        if(argc == 3){
          printf("Sequential wall clock time: %f sec\n", seq_time);
        }

        /*Parallel Implementation using Pthreads*/ 

        pthread_t thread;
        sortarg parg;
        /* sort elements in original order */
        pthread_mutex_init(&mutex,NULL);
        threadCounter = 0;

        gettimeofday (&startwtime, NULL);
        parg.a = a_par;
        parg.n = n;

        pthread_mutex_lock (&mutex);
        threadCounter++;
        pthread_mutex_unlock (&mutex);

        rep = pthread_create(&thread, NULL, wrapper, (void *)&parg);

        pthread_join(thread,NULL);

        gettimeofday (&endwtime, NULL);

        /* get time in seconds */
        par_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                            + endwtime.tv_sec - startwtime.tv_sec);
        //print(a_par, n);
        /* validate result */
        pass = test(a_par, n);
        if(argc == 3){
          printf(" TEST %s\n",(pass) ? "PASSed" : "FAILed");
        }
        assert( pass != 0 );
        /* print sorted vector */
        /* print(a, n); */
        
        /* print execution time */
        if(argc == 3){
          printf("Parallel wall clock time: %f sec\n", par_time);
          printf("Parallel to Serial excecution time acceleration was: %f\n",seq_time/par_time);
        }
        mean_qsort += qsort_time;
        mean_seq += seq_time;
        mean_par += par_time;
        free(a_qsort);
        free(a_seq);
        free(a_par);
      }
      mean_qsort = mean_qsort/meanSize;
      mean_seq = mean_seq/meanSize;
      mean_par = mean_par/meanSize;
      if(argc == 5){
        printf("Size = 2^%d Threads = 2^%d\n", n_it, thr_it);
        fprintf(f,"%d,%d,%f,%f,%f\n", 1<<n_it, 1<<thr_it,mean_qsort,mean_seq,mean_par);
      }
    }
  }
  
  if(argc == 5){
    fclose(f);
    printf("File pthread_data.csv  was written successfully\n");
  }
  /* exit */
  return 0;
  
}

/** -------------- SUB-PROCEDURES  ----------------- **/ 

/** procedure test() : verify sort results **/
int test(int *a, int n) {

  // TODO: implement
  int pass = 1;
  for (int i=0;i<n-1;i++)
    if(a[i] > a[i+1])
      pass = 0;
  
  return (pass);
  
}

/** procedure copy() : copy contents of array b to array a **/
void copy(int *a, int *b, int n) {
  int i;
  for (i = 0; i < n; i++) {
    a[i] = b[i];
  }
}

/** procedure init() : initialize array "a" with data **/
void init(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    a[i] = rand() % n; // (N - i);
  }
}

/** procedure  print() : print array elements **/
void print(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}