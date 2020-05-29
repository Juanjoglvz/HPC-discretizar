#!/usr/bin/make -f
# -*- mode:makefile -*-

FLAGS := -fopenmp -lm
CC := gcc

DIROBJ := obj/
DIRSRC := src/

all: dirs discretizo_secuencial discretizo_paralelo

dirs:
	mkdir -p $(DIROBJ)
	
	
discretizo_secuencial: $(DIRSRC)discretizo_secuencial.c
	$(CC) -o $@ $^ $(FLAGS)

discretizo_paralelo: $(DIRSRC)discretizo_paralelo.c
	$(CC) -o $@ $^ $(FLAGS)

$(DIROBJ)%.o: $(DIRSRC)%.c
	$(CC) -c $^ -o $@ $(FLAGS)
	
	
clean: 
	-$(RM) *~
	-$(RM) -r ./obj
	-$(RM) discretizo_secuencial discretizo_paralelo

