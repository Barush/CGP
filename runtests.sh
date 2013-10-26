#!/bin/sh

mkdir test3x3_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test3x3_10/time$i.txt ./cocgp testdata.txt -r 3 -c 3 -g 10 >> test3x3_10/nightTest$i.txt
done

mkdir test3x4_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test3x4_10/time$i.txt ./cocgp testdata.txt -r 3 -c 4 -g 10 >> test3x4_10/nightTest$i.txt
done

mkdir test3x5_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test3x5_10/time$i.txt ./cocgp testdata.txt -r 3 -c 5 -g 10 >> test3x5_10/nightTest$i.txt
done

mkdir test3x6_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test3x6_10/time$i.txt ./cocgp testdata.txt -r 3 -c 6 -g 10 >> test3x6_10/nightTest$i.txt
done

mkdir test3x7_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test3x7_10/time$i.txt ./cocgp testdata.txt -r 3 -c 7 -g 10 >> test3x7_10/nightTest$i.txt
done

mkdir test3x8_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test3x8_10/time$i.txt ./cocgp testdata.txt -r 3 -c 8 -g 10 >> test3x8_10/nightTest$i.txt
done

mkdir test4x3_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test4x3_10/time$i.txt ./cocgp testdata.txt -r 4 -c 3 -g 10 >> test4x3_10/nightTest$i.txt
done

mkdir test4x4_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test4x4_10/time$i.txt ./cocgp testdata.txt -r 4 -c 4 -g 10 >> test3x4_10/nightTest$i.txt
done

mkdir test4x5_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test4x5_10/time$i.txt ./cocgp testdata.txt -r 4 -c 5 -g 10 >> test4x5_10/nightTest$i.txt
done

mkdir test4x6_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test4x6_10/time$i.txt ./cocgp testdata.txt -r 4 -c 6 -g 10 >> test4x6_10/nightTest$i.txt
done

mkdir test4x7_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test4x7_10/time$i.txt ./cocgp testdata.txt -r 4 -c 7 -g 10 >> test4x7_10/nightTest$i.txt
done

mkdir test4x8_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test4x8_10/time$i.txt ./cocgp testdata.txt -r 4 -c 8 -g 10 >> test4x8_10/nightTest$i.txt
done

mkdir test5x3_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test5x3_10/time$i.txt ./cocgp testdata.txt -r 5 -c 3 -g 10 >> test5x3_10/nightTest$i.txt
done

mkdir test5x4_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test5x4_10/time$i.txt ./cocgp testdata.txt -r 5 -c 4 -g 10 >> test5x4_10/nightTest$i.txt
done

mkdir test5x5_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test5x5_10/time$i.txt ./cocgp testdata.txt -r 5 -c 5 -g 10 >> test5x5_10/nightTest$i.txt
done

mkdir test5x6_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test5x6_10/time$i.txt ./cocgp testdata.txt -r 5 -c 6 -g 10 >> test5x6_10/nightTest$i.txt
done

mkdir test5x7_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test5x7_10/time$i.txt ./cocgp testdata.txt -r 5 -c 7 -g 10 >> test5x7_10/nightTest$i.txt
done

mkdir test5x8_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test5x8_10/time$i.txt ./cocgp testdata.txt -r 5 -c 8 -g 10 >> test5x8_10/nightTest$i.txt
done

mkdir test6x3_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test6x3_10/time$i.txt ./cocgp testdata.txt -r 5 -c 3 -g 10 >> test5x3_10/nightTest$i.txt
done

mkdir test6x4_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test6x4_10/time$i.txt ./cocgp testdata.txt -r 5 -c 4 -g 10 >> test5x4_10/nightTest$i.txt
done

mkdir test6x5_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test6x5_10/time$i.txt ./cocgp testdata.txt -r 5 -c 5 -g 10 >> test5x5_10/nightTest$i.txt
done

mkdir test6x6_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test6x6_10/time$i.txt ./cocgp testdata.txt -r 5 -c 6 -g 10 >> test5x6_10/nightTest$i.txt
done

mkdir test6x7_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test6x7_10/time$i.txt ./cocgp testdata.txt -r 5 -c 7 -g 10 >> test5x7_10/nightTest$i.txt
done

mkdir test6x8_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test6x8_10/time$i.txt ./cocgp testdata.txt -r 5 -c 8 -g 10 >> test5x8_10/nightTest$i.txt
done

mkdir test7x3_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test7x3_10/time$i.txt ./cocgp testdata.txt -r 5 -c 3 -g 10 >> test5x3_10/nightTest$i.txt
done

mkdir test7x4_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test7x4_10/time$i.txt ./cocgp testdata.txt -r 5 -c 4 -g 10 >> test5x4_10/nightTest$i.txt
done

mkdir test7x5_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test7x5_10/time$i.txt ./cocgp testdata.txt -r 5 -c 5 -g 10 >> test5x5_10/nightTest$i.txt
done

mkdir test7x6_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test7x6_10/time$i.txt ./cocgp testdata.txt -r 5 -c 6 -g 10 >> test5x6_10/nightTest$i.txt
done

mkdir test7x7_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test7x7_10/time$i.txt ./cocgp testdata.txt -r 5 -c 7 -g 10 >> test5x7_10/nightTest$i.txt
done

mkdir test7x8_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test7x8_10/time$i.txt ./cocgp testdata.txt -r 5 -c 8 -g 10 >> test5x8_10/nightTest$i.txt
done

mkdir test8x3_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test8x3_10/time$i.txt ./cocgp testdata.txt -r 5 -c 3 -g 10 >> test5x3_10/nightTest$i.txt
done

mkdir test8x4_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test8x4_10/time$i.txt ./cocgp testdata.txt -r 5 -c 4 -g 10 >> test5x4_10/nightTest$i.txt
done

mkdir test8x5_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test8x5_10/time$i.txt ./cocgp testdata.txt -r 5 -c 5 -g 10 >> test5x5_10/nightTest$i.txt
done

mkdir test8x6_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test8x6_10/time$i.txt ./cocgp testdata.txt -r 5 -c 6 -g 10 >> test5x6_10/nightTest$i.txt
done

mkdir test8x7_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test8x7_10/time$i.txt ./cocgp testdata.txt -r 5 -c 7 -g 10 >> test5x7_10/nightTest$i.txt
done

mkdir test8x8_10

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
do
	time 2> test8x8_10/time$i.txt ./cocgp testdata.txt -r 5 -c 8 -g 10 >> test5x8_10/nightTest$i.txt
done