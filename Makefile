######################################
# Nazev: Makefile
# Ucel kodu: IPK projekt 2
#      makefile pro preklad programu klient - server
# Autor: Barbora Skrivankova, xskriv01, FIT VUT
# Vytvoreno: brezen 2013
######################################

CPPFLAGS = --std=c++98 -pedantic -g 
LIBS = -lm -pthread -lrt
CC = g++ $(CPPFLAGS)
OBJ = creategen.o iowork.o evalexpre.o evolution.o coevolution.o

executable: cgp coecgp generateData

cgp: cocgp.cpp $(OBJ)
	$(CC) -o cgp cocgp.cpp $(OBJ) $(LIBS)

coecgp: cocgp.cpp $(OBJ)
	$(CC) -o coecgp cocgp.cpp $(OBJ) -DCOEVOLUTION $(LIBS)

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

#coevolution.o: coevolution.h coevolution.cpp
	#$(CC) -c coevolution.cpp

run:
	./cgp testdata.txt func.txt -r 1 -c 30 -t 0.1 -l 30

coev:
	./coecgp testdata.txt func.txt -r 1 -c 30 -t 0.1 -l 30

clean: 
	rm -f *.o
	rm cgp
	rm generateData
	rm coecgp
