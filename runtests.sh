#!/bin/sh

mkdir test4x20_10

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test4x20_10/time$i.txt ./cocgp testdata.txt -r 4 -c 20 -g 10 >> test4x20_10/test$i.txt 2> test4x20_10/result$i.txt
done

mkdir test8x10_10

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test8x10_10/time$i.txt ./cocgp testdata.txt -r 8 -c 10 -g 10 >> test8x10_10/test$i.txt 2> test8x10_10/result$i.txt
done

mkdir test5x16_10

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test5x16_10/time$i.txt ./cocgp testdata.txt -r 5 -c 16 -g 10 >> test5x16_10/test$i.txt 2> test5x16_10/result$i.txt
done

mkdir test9x9_10

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test9x9_10/time$i.txt ./cocgp testdata.txt -r 9 -c 9 -g 10 >> test9x9_10/test$i.txt 2> test9x9_10/result$i.txt
done

mkdir test3x30_10

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test3x30_10/time$i.txt ./cocgp testdata.txt -r 3 -c 30 -g 10 >> test3x30_10/test$i.txt 2> test3x30_10/result$i.txt
done
