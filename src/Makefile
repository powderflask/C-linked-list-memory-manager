all: fstest mmtest

fstest: freestore.h freestore.c fs-tests.c
	gcc freestore.c fs-tests.c -o fstest

mmtest: freestore.h freestore.c segList.h segList.c mmalloc.h mmalloc.c mm-tests.c
	gcc freestore.c segList.c mmalloc.c mm-tests.c -o mmtest

clean:
	@rm -f *.o fstest mmtest