######################################
# Nazev: Makefile
# Ucel kodu: IPK projekt 2
#      makefile pro preklad programu klient - server
# Autor: Barbora Skrivankova, xskriv01, FIT VUT
# Vytvoreno: brezen 2013
######################################

CPPFLAGS = --std=c++98 -pedantic -g 
COECPPFLAGS = --std=c++98 -pedantic -g -DCOEVOLUTION
LIBS = -lm -pthread -lrt
CC = g++ $(CPPFLAGS)
COECC = g++ $(COECPPFLAGS)
OBJ = creategen.o iowork.o evalexpre.o evolution.o coevolution.o
COEOBJ = c_creategen.o c_iowork.o c_evalexpre.o c_evolution.o c_coevolution.o

executable: generateData cgp coecgp 

cgp: cocgp.cpp $(OBJ)
	$(CC) -o cgp cocgp.cpp $(OBJ) $(LIBS)

coecgp: cocgp.cpp $(COEOBJ)
	$(COECC) -o coecgp cocgp.cpp $(COEOBJ) $(LIBS)

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

c_creategen.o: creategen.h creategen.cpp
	$(COECC) -c creategen.cpp -o c_creategen.o

c_iowork.o: iowork.h iowork.cpp
	$(COECC) -c iowork.cpp -o c_iowork.o

c_evalexpre.o: evalexpre.h evalexpre.cpp
	$(COECC) -c evalexpre.cpp -o c_evalexpre.o

c_evolution.o: evolution.h evolution.cpp
	$(COECC) -c evolution.cpp -o c_evolution.o

c_coevolution.o: coevolution.h coevolution.cpp
	$(COECC) -c coevolution.cpp -o c_coevolution.o

#coevolution.o: coevolution.h coevolution.cpp
	#$(CC) -c coevolution.cpp

run:
	./cgp ./testfiles/x_2_3.txt func.txt -r 1 -c 32 -t 0.1 -l 32 -g 12

coev:
	./coecgp ./testfiles/x_2_3.txt func.txt -r 1 -c 32 -t 0.025 -l 32 -p 2 -s 10 -cg 20 -a 1

clean: 
	rm -f *.o
	rm cgp
	rm generateData
	rm coecgp
