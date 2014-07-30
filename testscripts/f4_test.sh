#!/bin/sh

###############################################################################
#############  F4: 30 runs without coev, 30 runs with coev  ###################
###############################################################################

mkdir ../f4

for i in `seq 1 30`
do 
	../cgp ../testfiles/f4.txt ../testfiles/func.txt -r 1 -c 32 -g 12 -t 0.025 -l 32 >> ../f4/test$i.txt 2> ../f4/result$i.txt
done

mkdir ../f4_coev

for i in `seq 1 30`
do 
	../coecgp ../testfiles/f4.txt ../testfiles/func.txt -r 1 -c 32 -g 12 -t 0.025 -l 32 -a 2 -p 3 -s 16 -cg 32 -b 8 -ch 16   >> ../f4_coev/test$i.txt 2> ../f4_coev/result$i.txt
done
