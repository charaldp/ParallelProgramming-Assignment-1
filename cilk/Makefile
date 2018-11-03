
GCC = gcc
CFLAGS = -fcilkplus -O3

CMAIN = qsort_cilk

all: qsort-main-cilk.o qsort-cilk.o qsort-sequential.o
	$(GCC) $(CFLAGS) $^ -o $(CMAIN)

%.o: %.c
	$(GCC) -c $(CFLAGS) $^

clean:
	rm -f *.o *~ $(CMAIN)
