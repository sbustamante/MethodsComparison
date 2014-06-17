#==============================================================================
#	GADGET MISCELLANEOUS
#==============================================================================
# Sebastian Bustamante (Universidad de Antioquia), sebastian.bustamante@gmail.com

CC=gcc
CFLAGS=-g -I. -c

#Cutter
Cutter:inout.o miscellaneous.o Cutter.o
	gcc inout.o miscellaneous.o Cutter.o -lm -o Cutter.out
	rm -r *.o

edit:
	kate *.c *.h &

clean:
	rm -r *.o *.out *.png *.tmp