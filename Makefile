######################################
# Nazev: Makefile
# Ucel kodu: IPK projekt 2
#      makefile pro preklad programu klient - server
# Autor: Barbora Skrivankova, xskriv01, FIT VUT
# Vytvoreno: brezen 2013
######################################

CPPFLAGS=--std=c++98 -Wall -pedantic -g

all: main

main: main.o
	g++ $(CPPFLAGS) main.o -o main

main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp

clean: 
	rm -f *.o
	rm main