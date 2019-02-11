all: sltest fstest mmtest

sltest: segList.h segList.c sl-tests.c
	gcc segList.c sl-tests.c -o sltest

fstest: freestore.h freestore.c segList.h segList.c fs-tests.c
	gcc freestore.c segList.c fs-tests.c -o fstest

mmtest: freestore.h freestore.c segList.h segList.c mmalloc.h mmalloc.c mm-tests.c
	gcc freestore.c segList.c mmalloc.c mm-tests.c -o mmtest

clean:
	@rm -f *.o sltest fstest mmtest