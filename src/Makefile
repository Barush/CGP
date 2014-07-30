################################################################################
######################### COEVOLUTION IN CGP ###################################
########################## BACHELORS THESIS ####################################
######################## BARBORA SKRIVANKOVA ###################################
###################### xskri01@stud.fit.vutbr.cz ###############################
################################################################################

################## MAKEFILE FOR ALL BINARIES IN THESIS #########################
### file name: 			Makefile
###	creation date:		01/2014
################################################################################


CPPFLAGS = --std=c++98 -pedantic -g 
COECPPFLAGS = --std=c++98 -pedantic -g -DCOEVOLUTION
LIBS = -lm -pthread
OS := $(shell uname -s)
ifeq ($(OS),Linux)
LIBS += -lrt
endif
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

run:
	./cgp ../testfiles/f1.txt ../testfiles/func.txt -r 1 -c 32 -t 0.5 -l 32 -g 12

coev:
	./coecgp ../testfiles/f1.txt ../testfiles/func.txt -r 1 -c 32 -g 12 -t 0.5 -l 32 -a 2 -p 3 -s 8 -cg 32 -b 8 -ch 16

clean: 
	rm -f *.o
	rm cgp
	rm generateData
	rm coecgp
