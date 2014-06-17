#==============================================================================
#	GADGET MISCELLANEOUS
#==============================================================================
# Sebastian Bustamante (Universidad de Antioquia), sebastian.bustamante@gmail.com

CC	=	gcc
CFLAGS	=	-g -I. -c

#Cutter
Cutter:	inout.o miscellaneous.o Cutter.o
	$(CC) inout.o miscellaneous.o Cutter.o -lm -o Cutter.out
	rm -r *.o
	
#Ascii
Ascii:	inout.o miscellaneous.o Ascii.o
	$(CC) inout.o miscellaneous.o Ascii.o -lm -o Ascii.out
	rm -r *.o
	
#Compile all
All:	inout.o miscellaneous.o Cutter.o Ascii.o
	$(CC) inout.o miscellaneous.o Cutter.o -lm -o Cutter.out
	$(CC) inout.o miscellaneous.o Ascii.o -lm -o Ascii.out
	rm -r *.o

edit:
	kate *.c *.h &

clean:
	rm -r *.o *.out *.png *.tmp