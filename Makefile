DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/

CC := gcc-8
CFLAGS := -c -Wall -Wextra -Wpedantic -O2 -fopenmp -lm
LDLIBS := -L$(DIROBJ) -fopenmp -lm


all: dirs sequential discretizo

seq: sequential
	$(DIREXE)sequential

par: discretizo
	$(DIREXE)discretizo

sequential: $(DIROBJ)sequential.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

discretizo: $(DIROBJ)discretizo.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

$(DIROBJ)%.o: $(DIRSRC)%.c
	$(CC) $(CFLAGS) $^ -o $@

dirs:
	mkdir -p $(DIROBJ) $(DIRLIB) $(DIREXE)

clean: 
	$(RM) -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~
	
.PHONY: all, dirs, seq, par, sequential, discretizo, clean
