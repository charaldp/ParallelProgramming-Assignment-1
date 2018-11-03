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

#ifndef _QSORT_OMP_H_
#define _QSORT_OMP_H_

/* qsortseq -- Sort vector v (of length n) using QuickSort */
void qsort_omp(int *v, int n);

#endif /* _QSORT-SEQUENTIAL_H_ */



