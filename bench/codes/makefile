#==============================================================================
#	GADGET MISCELLANEOUS
#==============================================================================
# Sebastian Bustamante (Universidad de Antioquia), sebastian.bustamante@gmail.com

CC	=	gcc
CFLAGS	=	-g -I. -c

#Cutter
Cutter:	inout.o miscellaneous.o gas.o Cutter.o
	$(CC) inout.o miscellaneous.o gas.o Cutter.o -lm -o Cutter.out
	rm -r *.o
	
#Ascii
Ascii:	inout.o miscellaneous.o gas.o Ascii.o
	$(CC) inout.o miscellaneous.o gas.o Ascii.o -lm -o Ascii.out
	rm -r *.o
	
#Halos
Halos:	inout.o miscellaneous.o gas.o Halos.o
	$(CC) inout.o miscellaneous.o gas.o Halos.o -lm -o Halos.out
	rm -r *.o
	
#g2tog1
g2tog1:	g2tog1.o
	$(CC) g2tog1.o -lm -o g2tog1.out
	rm -r *.o
	
#Compile all
All:	g2tog1.o gas.o inout.o miscellaneous.o Cutter.o Ascii.o Halos.o
	$(CC) inout.o miscellaneous.o gas.o Cutter.o -lm -o Cutter.out
	$(CC) inout.o miscellaneous.o gas.o Ascii.o -lm -o Ascii.out
	$(CC) inout.o miscellaneous.o gas.o Halos.o -lm -o Halos.out
	$(CC) g2tog1.o -lm -o g2tog1.out
	rm -r *.o

edit:
	kate *.c *.h &

clean:
	rm -r *.o *.out *.png *.tmp