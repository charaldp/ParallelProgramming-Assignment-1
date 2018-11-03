
GCC = gcc
CFLAGS = -O3 -fopenmp

CMAIN = qsort_omp

all: qsort-main-omp.o qsort-omp.o qsort-sequential.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)
