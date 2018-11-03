/**********************************************************************
 *
 * qsort-pthreads.c -- Parallel implementation of QuickSort using prthreads
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Further Edits:
 * Charalampos Papadiakos <charaldp@auth.gr>
 * Time-stamp: <2018-11-4>
 *
 **********************************************************************/


#include <stdio.h>
#include <pthread.h>
#include "qsort-sequential.h"

int rep;
extern int threadCounter,userDefinedThreads;
extern pthread_mutex_t mutex;

void qsort_pthread(int *v, int n);

typedef struct { int *a, n;
} sortarg;

void * wrapper (void *arg) {
  int *ap; 
  int nn, tid;
  ap = ((sortarg *) arg) ->a;
  nn = ((sortarg *) arg)->n;
  qsort_pthread(ap,nn);
}

/* swap -- swap elements k and l of vector v */
void swap_pthread(int *v, int k, int l) {
  int temp = v[k];
  v[k] = v[l];
  v[l] = temp;
}


/* partition -- in-place update of elements */
int partition_pthread(int *v, int n) {
  int pivot = v[n-1];
  int i = 0;
  
  for (int j = 0; j < n - 1; j++) 
    if (v[j] < pivot) 
      swap_pthread(v,i++,j);

  swap_pthread(v, i, n - 1);
  return (i);
}

/* qsortseq -- Entry point for QuickSort */
void qsort_pthread(int *v, int n) {

  if (n > 1) {
    int p = partition_pthread(v, n);
    if(threadCounter <= userDefinedThreads && n > 1<<12){
      pthread_mutex_lock (&mutex);
      threadCounter++;
      pthread_mutex_unlock (&mutex);
      pthread_t thread;
      sortarg parg;
      parg.a = v;
      parg.n = p;

      rep = pthread_create(&thread, NULL, wrapper, (void *)&parg);
      qsort_pthread(&v[p+1],n-p-1);
      pthread_join(thread,NULL);

      pthread_mutex_lock (&mutex);
      threadCounter--;
      pthread_mutex_unlock (&mutex);
    }
    else{
      qsort_pthread(v,p);
      qsort_pthread(&v[p+1],n-p-1);
    }    
  }
}





