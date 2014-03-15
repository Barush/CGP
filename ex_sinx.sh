#!/bin/sh

mkdir Sinx_ex_30

mkdir Sinx_ex_80

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cocgp salustowitz.txt func.txt -r 1 -c 80 -g 5 -t 0.001 -l 80 >> Sinx_ex_80/test$i.txt 2> Sinx_ex_80/result$i.txt
done

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cocgp salustowitz.txt func.txt -r 1 -c 30 -g 5 -t 0.001 -l 30 >> Sinx_ex_30/test$i.txt 2> Sinx_ex_30/result$i.txt
done

mkdir Sinx_ex_40

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cocgp salustowitz.txt func.txt -r 1 -c 40 -g 5 -t 0.001 -l 40 >> Sinx_ex_40/test$i.txt 2> Sinx_ex_40/result$i.txt
done

mkdir Sinx_ex_50

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cocgp salustowitz.txt func.txt -r 1 -c 50 -g 5 -t 0.001 -l 50 >> Sinx_ex_50/test$i.txt 2> Sinx_ex_50/result$i.txt
done

mkdir Sinx_ex_60

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cocgp salustowitz.txt func.txt -r 1 -c 60 -g 5 -t 0.001 -l 60 >> Sinx_ex_60/test$i.txt 2> Sinx_ex_60/result$i.txt
done

mkdir Sinx_ex_70

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cocgp salustowitz.txt func.txt -r 1 -c 70 -g 5 -t 0.001 -l 70 >> Sinx_ex_70/test$i.txt 2> Sinx_ex_70/result$i.txt
done
