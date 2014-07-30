#!/bin/sh

###############################################################################
#############  F3: 50 runs without coev, 50 runs with coev  ###################
###############################################################################

mkdir ../f3

for i in `seq 1 50`
do 
	../cgp ../testfiles/f3.txt ../testfiles/func.txt -r 1 -c 32 -g 12 -t 1.5 -l 32 >> ../f3/test$i.txt 2> ../f3/result$i.txt
done

mkdir ../f3_coev

for i in `seq 1 50`
do 
	../coecgp ../testfiles/f3.txt ../testfiles/func.txt -r 1 -c 32 -g 12 -t 1.5 -l 32 -a 2 -p 3 -s 8 -cg 32 -b 8 -ch 16   >> ../f3_coev/test$i.txt 2> ../f3_coev/result$i.txt
done
