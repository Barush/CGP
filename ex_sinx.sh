#!/bin/sh

mkdir Sinx_ex_20

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cgp salustowitz.txt func.txt -r 1 -c 20 -g 5 -t 0.025 -l 20 >> Sinx_ex_20/test$i.txt 2> Sinx_ex_20/result$i.txt
done

mkdir Sinx_ex_30

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cgp salustowitz.txt func.txt -r 1 -c 30 -g 5 -t 0.025 -l 30 >> Sinx_ex_30/test$i.txt 2> Sinx_ex_30/result$i.txt
done

mkdir Sinx_ex_40

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cgp salustowitz.txt func.txt -r 1 -c 40 -g 5 -t 0.025 -l 40 >> Sinx_ex_40/test$i.txt 2> Sinx_ex_40/result$i.txt
done

mkdir Sinx_ex_50

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cgp salustowitz.txt func.txt -r 1 -c 50 -g 5 -t 0.025 -l 50 >> Sinx_ex_50/test$i.txt 2> Sinx_ex_50/result$i.txt
done

mkdir Sinx_ex_60

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
do
	./cgp salustowitz.txt func.txt -r 1 -c 60 -g 5 -t 0.025 -l 60 >> Sinx_ex_60/test$i.txt 2> Sinx_ex_60/result$i.txt
done
