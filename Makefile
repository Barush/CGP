######################################
# Nazev: Makefile
# Ucel kodu: IPK projekt 2
#      makefile pro preklad programu klient - server
# Autor: Barbora Skrivankova, xskriv01, FIT VUT
# Vytvoreno: brezen 2013
######################################

CPPFLAGS = --std=c++98 -Wall -pedantic -g -lm -pthread
CC = g++ $(CPPFLAGS)
OBJ = creategen.o iowork.o evalexpre.o evolution.o coevolution.o

executable: cocgp generateData

cocgp: cocgp.cpp $(OBJ)
	$(CC) -o cocgp cocgp.cpp $(OBJ)

generateData: generateData.c
	gcc -std=c99 -Wall -pedantic -g -o generateData generateData.c -lm

creategen.o: creategen.h creategen.cpp
	$(CC) -c creategen.cpp

iowork.o: iowork.h iowork.cpp
	$(CC) -c iowork.cpp

evalexpre.o: evalexpre.h evalexpre.cpp
	$(CC) -c evalexpre.cpp

evolution.o: evolution.h evolution.cpp
	$(CC) -c evolution.cpp

coevolution.o: coevolution.h coevolution.cpp
	$(CC) -c coevolution.cpp

run:
	./cocgp testdata.txt -c 5 -r 3 2>err.txt

clean: 
	rm -f *.o
	rm cocgp
	rm generateData
