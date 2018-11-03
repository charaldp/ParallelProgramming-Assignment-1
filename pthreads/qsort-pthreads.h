/**********************************************************************
 *
 * qsort-pthreads.h -- Parallel implementation of QuickSort using prthreads
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Further Edits:
 * Charalampos Papadiakos <charaldp@auth.gr>
 * Time-stamp: <2018-11-4>
 *
 **********************************************************************/


#ifndef _QSORT_PTHREADS_H_
#define _QSORT_PTHREADS_H_

//int counter;

/* qsortseq -- Sort vector v (of length n) using QuickSort */
void qsort_pthread(int *v, int n);
void * wrapper (void *arg);

#endif /* _QSORT-SEQUENTIAL_H_ */



