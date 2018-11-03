
GCC = gcc
CFLAGS = -O3

CMAIN = qsort_pthreads

all: qsort-main-pthreads.o qsort-pthreads.o qsort-sequential.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN) -lpthread

%.o: %.c
	$(GCC) -c $(CFLAGS) $^ -lpthread

clean:
	rm -f *.o *~ $(CMAIN)
