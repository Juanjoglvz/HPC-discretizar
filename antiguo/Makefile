DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/

CC := gcc-8
CFLAGS := -c -Wall -Wextra -Wpedantic -O2 -fopenmp -lm
LDLIBS := -L$(DIROBJ) -fopenmp -lm


all: dirs sequential parallel_outputdec parallel_outputdec_reduction parallel_inputdec parallel_inputdec_reduction parallel_inputoutput

seq: sequential
	$(DIREXE)sequential

par_o: parallel_outputdec
	$(DIREXE)parallel_outputdec

par_o_red: parallel_outputdec_reduction
	$(DIREXE)parallel_outputdec_reduction

par_i: parallel_inputdec
	$(DIREXE)parallel_inputdec

par_i_red: parallel_inputdec_reduction
	$(DIREXE)parallel_inputdec_reduction

par_io: parallel_inputoutput
	$(DIREXE)parallel_inputoutput

sequential: $(DIROBJ)sequential.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

parallel_outputdec: $(DIROBJ)parallel_outputdec.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

parallel_outputdec_reduction: $(DIROBJ)parallel_outputdec_reduction.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

parallel_inputdec: $(DIROBJ)parallel_inputdec.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

parallel_inputdec_reduction: $(DIROBJ)parallel_inputdec_reduction.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

parallel_inputoutput: $(DIROBJ)parallel_inputoutput.o
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

$(DIROBJ)%.o: $(DIRSRC)%.c
	$(CC) $(CFLAGS) $^ -o $@

dirs:
	mkdir -p $(DIROBJ) $(DIRLIB) $(DIREXE)

clean: 
	$(RM) -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~
	
.PHONY: all, dirs, seq, par_o, par_o_red, sequential, parallel_outputdec, parallel_outputdec_reduction, parallel_inputdec, parallel_inputdec_reduction, parallel_inputoutput, clean
