GCC = gcc-9
FLAGS = -pedantic -Wall
CFLAGS = -lm -lpthread

PROGS: MM1c MM1f MMPosix

MM1c:
	$(GCC) $(FLAGS) module.c -c $(FLAGS)
	$(GCC) $(FLAGS) $@.c -c 
	$(GCC) $(FLAGS) module.o $@.o -o $@ 
	
MM1f:
	$(GCC) $(FLAGS) module.c -c $(FLAGS)
	$(GCC) $(FLAGS) $@.c -c 
	$(GCC) $(FLAGS) module.o $@.o -o $@
		
MMPosix:
	$(GCC) $(FLAGS) module.c -c $(CFLAGS)
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS) 
	$(GCC) $(FLAGS) module.o $@.o -o $@ $(CFLAGS) 

clean:
	$(RM) $(PROGS) *.o
	$(RM) MM1c MM1f MMPosix
