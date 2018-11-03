/**********************************************************************
 *
 * qsort-omp.h -- Parallel implementation of QuickSort using OpenMP
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Charalampos Papadiakos <charaldp@auth.gr>
 * Time-stamp: <2018-11-4>
 *
 **********************************************************************/


#include <stdio.h>
#include <omp.h>
#include "qsort-sequential.h"

/* swap -- swap elements k and l of vector v */
void swap_omp(int *v, int k, int l) {
  int temp = v[k];
  v[k] = v[l];
  v[l] = temp;
}



/* partition -- in-place update of elements */
int partition_omp(int *v, int n) {
  int pivot = v[n-1];
  int i = 0;
  //printf("ID = %d Threads = %d\n",omp_get_thread_num(),omp_get_num_threads());
  //#pragma omp for schedule(dynamic,8)
  for (int j = 0; j < n - 1; j++){
  //printf("j = %d ID = %d Threads = %d\n",j,omp_get_thread_num(),omp_get_num_threads());
    if (v[j] < pivot) 
      swap_omp(v,i++,j);
  }
  swap_omp(v, i, n - 1);
  return (i);
}

/* qsortseq -- Entry point for QuickSort */
void qsort_omp(int *v, int n) {
  //printf("ID = %d Threads = %d\n",omp_get_thread_num(),omp_get_num_threads());
   if (n > 1){
    int p = partition_omp(v, n);

    #pragma omp task if (p > 1<<9)
      qsort_omp(v,p);

    //#pragma omp task if (n-p-1 > 1<<9)
      qsort_omp(&v[p+1],n-p-1);

}

}


