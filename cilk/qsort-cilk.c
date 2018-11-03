/**********************************************************************
 *
 * qsort-cilk.c -- Parallel implementation of QuickSort using Cilk
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Further edits
 * Charalampos Papadiakos <charaldp@auth.gr>
 * Time-stamp: <2018-11-4>
 *
 **********************************************************************/


#include <stdio.h>
#include <cilk/cilk.h>

/* swap -- swap elements k and l of vector v */
void swap_cilk(int *v, int k, int l) {
  int temp = v[k];
  v[k] = v[l];
  v[l] = temp;
}


/* partition -- in-place update of elements */
int partition_cilk(int *v, int n) {
  int pivot = v[n-1];
  int i = 0;
  
  for (int j = 0; j < n - 1; j++) 
    if (v[j] < pivot) 
      swap_cilk(v,i++,j);

  swap_cilk(v, i, n - 1);
  return (i);
}

/* qsortseq -- Entry point for QuickSort */
void qsort_cilk(int *v, int n) {
  if (n > 1) {
    int p = partition_cilk(v, n);
    if(p > 1<<9 || n-p-1 > 1<<9){
      if(p > 1<<9 && n-p-1 > 1<<9){
        cilk_spawn qsort_cilk(v,p);
        cilk_spawn qsort_cilk(&v[p+1],n-p-1);
      }
      else if(p > 1<<9) {
        cilk_spawn qsort_cilk(v,p);
        qsort_cilk(&v[p+1],n-p-1);
      }
      else{
        cilk_spawn qsort_cilk(&v[p+1],n-p-1);
        qsort_cilk(v,p);
      }
      cilk_sync;
    }
    else{
      qsort_cilk(v,p);
      qsort_cilk(&v[p+1],n-p-1);
    }
  }
}