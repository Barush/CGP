#!/bin/sh

mkdir Salustowitz50

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cocgp salustowitz.txt func.txt -r 1 -c 50 -g 5 -t 0.3 -l 50 >> Salustowitz50/test$i.txt 2> Salustowitz50/result$i.txt
done

mkdir Salustowitz60

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cocgp salustowitz.txt func.txt -r 1 -c 60 -g 5 -t 0.3 -l 60 >> Salustowitz60/test$i.txt 2> Salustowitz60/result$i.txt
done

mkdir Salustowitz70

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cocgp salustowitz.txt func.txt -r 1 -c 70 -g 5 -t 0.3 -l 70 >> Salustowitz70/test$i.txt 2> Salustowitz70/result$i.txt
done

###############################################################################