#!/bin/sh

###############################################################################
###########################  Unwrapped Ball_1D  ###############################
###############################################################################

mkdir gen_5/Unwrapped_Ball_20

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 20 -g 5 -t 0.025 -l 20 >> gen_5/Unwrapped_Ball_20/test$i.txt 2> gen_5/Unwrapped_Ball_20/result$i.txt
done

mkdir gen_5/Unwrapped_Ball_30

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 30 -g 5 -t 0.025 -l 30 >> gen_5/Unwrapped_Ball_30/test$i.txt 2> gen_5/Unwrapped_Ball_30/result$i.txt
done

mkdir gen_5/Unwrapped_Ball_40

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 40 -g 5 -t 0.025 -l 40 >> gen_5/Unwrapped_Ball_40/test$i.txt 2> gen_5/Unwrapped_Ball_40/result$i.txt
done

mkdir gen_5/Unwrapped_Ball_50

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 50 -g 5 -t 0.025 -l 50 >> gen_5/Unwrapped_Ball_50/test$i.txt 2> gen_5/Unwrapped_Ball_50/result$i.txt
done

mkdir gen_5/Unwrapped_Ball_60

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 60 -g 5 -t 0.025 -l 60 >> gen_5/Unwrapped_Ball_60/test$i.txt 2> gen_5/Unwrapped_Ball_60/result$i.txt
done

mkdir gen_5/Unwrapped_Ball_70

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 70 -g 5 -t 0.025 -l 70 >> gen_5/Unwrapped_Ball_70/test$i.txt 2> gen_5/Unwrapped_Ball_70/result$i.txt
done

mkdir gen_5/Unwrapped_Ball_80

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 80 -g 5 -t 0.025 -l 80 >> gen_5/Unwrapped_Ball_80/test$i.txt 2> gen_5/Unwrapped_Ball_80/result$i.txt
done

mkdir gen_5/Unwrapped_Ball_90

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 90 -g 5 -t 0.025 -l 90 >> gen_5/Unwrapped_Ball_90/test$i.txt 2> gen_5/Unwrapped_Ball_90/result$i.txt
done

mkdir gen_5/Unwrapped_Ball_100

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 100 -g 5 -t 0.025 -l 100 >> gen_5/Unwrapped_Ball_100/test$i.txt 2> gen_5/Unwrapped_Ball_100/result$i.txt
done

################################## MORE INDIVS IN GEN #########################

mkdir gen_10/Unwrapped_Ball_20

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 20 -g 10 -t 0.025 -l 20 >> gen_10/Unwrapped_Ball_20/test$i.txt 2> gen_10/Unwrapped_Ball_20/result$i.txt
done

mkdir gen_10/Unwrapped_Ball_30

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 30 -g 10 -t 0.025 -l 30 >> gen_10/Unwrapped_Ball_30/test$i.txt 2> gen_10/Unwrapped_Ball_30/result$i.txt
done

mkdir gen_10/Unwrapped_Ball_40

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 40 -g 10 -t 0.025 -l 40 >> gen_10/Unwrapped_Ball_40/test$i.txt 2> gen_10/Unwrapped_Ball_40/result$i.txt
done

mkdir gen_10/Unwrapped_Ball_50

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 50 -g 10 -t 0.025 -l 50 >> gen_10/Unwrapped_Ball_50/test$i.txt 2> gen_10/Unwrapped_Ball_50/result$i.txt
done

mkdir gen_10/Unwrapped_Ball_60

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 60 -g 10 -t 0.025 -l 60 >> gen_10/Unwrapped_Ball_60/test$i.txt 2> gen_10/Unwrapped_Ball_60/result$i.txt
done

mkdir gen_10/Unwrapped_Ball_70

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 70 -g 10 -t 0.025 -l 70 >> gen_10/Unwrapped_Ball_70/test$i.txt 2> gen_10/Unwrapped_Ball_70/result$i.txt
done

mkdir gen_10/Unwrapped_Ball_80

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 80 -g 10 -t 0.025 -l 80 >> gen_10/Unwrapped_Ball_80/test$i.txt 2> gen_10/Unwrapped_Ball_80/result$i.txt
done

mkdir gen_10/Unwrapped_Ball_90

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 90 -g 10 -t 0.025 -l 90 >> gen_10/Unwrapped_Ball_90/test$i.txt 2> gen_10/Unwrapped_Ball_90/result$i.txt
done

mkdir gen_10/Unwrapped_Ball_100

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 100 -g 10 -t 0.025 -l 100 >> gen_10/Unwrapped_Ball_100/test$i.txt 2> gen_10/Unwrapped_Ball_100/result$i.txt
done

################################## MORE INDIVS IN GEN #########################

mkdir gen_15/Unwrapped_Ball_20

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 20 -g 15 -t 0.025 -l 20 >> gen_15/Unwrapped_Ball_20/test$i.txt 2> gen_15/Unwrapped_Ball_20/result$i.txt
done

mkdir gen_15/Unwrapped_Ball_30

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 30 -g 15 -t 0.025 -l 30 >> gen_15/Unwrapped_Ball_30/test$i.txt 2> gen_15/Unwrapped_Ball_30/result$i.txt
done

mkdir gen_15/Unwrapped_Ball_40

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 40 -g 15 -t 0.025 -l 40 >> gen_15/Unwrapped_Ball_40/test$i.txt 2> gen_15/Unwrapped_Ball_40/result$i.txt
done

mkdir gen_15/Unwrapped_Ball_50

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 50 -g 15 -t 0.025 -l 50 >> gen_15/Unwrapped_Ball_50/test$i.txt 2> gen_15/Unwrapped_Ball_50/result$i.txt
done

mkdir gen_15/Unwrapped_Ball_60

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 60 -g 15 -t 0.025 -l 60 >> gen_15/Unwrapped_Ball_60/test$i.txt 2> gen_15/Unwrapped_Ball_60/result$i.txt
done

mkdir gen_15/Unwrapped_Ball_70

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 70 -g 15 -t 0.025 -l 70 >> gen_15/Unwrapped_Ball_70/test$i.txt 2> gen_15/Unwrapped_Ball_70/result$i.txt
done

mkdir gen_15/Unwrapped_Ball_80

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 80 -g 15 -t 0.025 -l 80 >> gen_15/Unwrapped_Ball_80/test$i.txt 2> gen_15/Unwrapped_Ball_80/result$i.txt
done

mkdir gen_15/Unwrapped_Ball_90

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 90 -g 15 -t 0.025 -l 90 >> gen_15/Unwrapped_Ball_90/test$i.txt 2> gen_15/Unwrapped_Ball_90/result$i.txt
done

mkdir gen_15/Unwrapped_Ball_100

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
do
	./cgp ball_1d.txt func.txt -r 1 -c 100 -g 15 -t 0.025 -l 100 >> gen_15/Unwrapped_Ball_100/test$i.txt 2> gen_15/Unwrapped_Ball_100/result$i.txt
done