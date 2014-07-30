#!/bin/sh

mkdir coev_test/cg_parts_16_3
mkdir coev_test/cg_parts_16_2
mkdir coev_test/cg_parts_16_1
mkdir coev_test/cg_parts_12_3
mkdir coev_test/cg_parts_12_2
mkdir coev_test/cg_parts_12_1

for i in `seq 1 30`
do
	./coecgp ./testfiles/x_2_3.txt func.txt -r 1 -c 32 -t 0.5 -l 32 -p 3 -s 8 -cg 32 -b 8 -ch 8 -a 2 >> coev_test/cg_parts_16_3/test$i.txt 2> coev_test/cg_parts_16_3/result$i.txt
done

for i in `seq 1 30`
do
	./coecgp ./testfiles/x_2_3.txt func.txt -r 1 -c 32 -t 0.5 -l 32 -p 3 -s 8 -cg 32 -b 8 -ch 16 -a 2 >> coev_test/cg_parts_16_2/test$i.txt 2> coev_test/cg_parts_16_2/result$i.txt
done

for i in `seq 1 30`
do
	./coecgp ./testfiles/x_2_3.txt func.txt -r 1 -c 32 -t 0.5 -l 32 -p 3 -s 8 -cg 32 -b 16 -ch 8 -a 2 >> coev_test/cg_parts_16_1/test$i.txt 2> coev_test/cg_parts_16_1/result$i.txt
done

for i in `seq 1 30`
do
	./coecgp ./testfiles/x_2_3.txt func.txt -r 1 -c 32 -t 0.5 -l 32 -p 3 -s 8 -cg 32 -b 10 -ch 10 -a 2 >> coev_test/cg_parts_12_3/test$i.txt 2> coev_test/cg_parts_12_3/result$i.txt
done

for i in `seq 1 30`
do
	./coecgp ./testfiles/x_2_3.txt func.txt -r 1 -c 32 -t 0.5 -l 32 -p 3 -s 8 -cg 32 -b 10 -ch 12 -a 2 >> coev_test/cg_parts_12_2/test$i.txt 2> coev_test/cg_parts_12_2/result$i.txt
done

for i in `seq 1 30`
do
	./coecgp ./testfiles/x_2_3.txt func.txt -r 1 -c 32 -t 0.5 -l 32 -p 3 -s 8 -cg 32 -b 12 -ch 10 -a 2 >> coev_test/cg_parts_12_1/test$i.txt 2> coev_test/cg_parts_12_1/result$i.txt
done