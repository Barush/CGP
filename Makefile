######################################
# Nazev: Makefile
# Ucel kodu: IPK projekt 2
#      makefile pro preklad programu klient - server
# Autor: Barbora Skrivankova, xskriv01, FIT VUT
# Vytvoreno: brezen 2013
######################################

CPPFLAGS = --std=c++98 -Wall -pedantic -g
CC = g++ $(CPPFLAGS)
OBJ = creategen.o iowork.o evalexpre.o

executable: cocgp generateData

cocgp: cocgp.cpp $(OBJ)
	$(CC) -o cocgp cocgp.cpp $(OBJ)

generateData: generateData.c
	gcc -std=c99 -Wall -pedantic -g -o generateData generateData.c

creategen.o: creategen.h creategen.cpp
	$(CC) -c creategen.cpp

iowork.o: iowork.h iowork.cpp
	$(CC) -c iowork.cpp

evalexpre.o: evalexpre.h evalexpre.cpp
	$(CC) -c evalexpre.cpp

clean: 
	rm -f *.o
	rm cocgp