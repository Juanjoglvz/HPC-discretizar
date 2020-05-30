DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/

CC := gcc-8
CFLAGS := -c -Wall -Wextra -Wpedantic -O2 -fopenmp -lm
LDLIBS := -L$(DIROBJ) -fopenmp -lm


all: dirs sequential parallel parallel_reduction

seq: sequential
	$(DIREXE)sequential

par: parallel
	$(DIREXE)parallel

red: parallel_reduction
	$(DIREXE)parallel_reduction

sequential: $(DIROBJ)sequential.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

parallel: $(DIROBJ)parallel.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

parallel_reduction: $(DIROBJ)parallel_reduction.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

$(DIROBJ)%.o: $(DIRSRC)%.c
	$(CC) $(CFLAGS) $^ -o $@

dirs:
	mkdir -p $(DIROBJ) $(DIRLIB) $(DIREXE)

clean: 
	$(RM) -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~
	
.PHONY: all, dirs, seq, par, red, sequential, parallel, parallel_reduction, clean
