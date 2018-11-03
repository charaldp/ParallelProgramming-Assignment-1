/**********************************************************************
 *
 * qsort-cilk.h -- Parallel implementation of QuickSort using Cilk
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Further edits
 * Charalampos Papadiakos <charaldp@auth.gr>
 * Time-stamp: <2018-11-4>
 *
 **********************************************************************/


#ifndef _QSORT_CILK_H_
#define _QSORT_CILK_H_

/* qsortseq -- Sort vector v (of length n) using QuickSort */
void qsort_cilk(int *v, int n);

#endif /* _QSORT-SEQUENTIAL_H_ */



