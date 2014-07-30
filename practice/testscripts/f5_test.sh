#!/bin/sh

###############################################################################
#############  F5: 30 runs without coev, 30 runs with coev  ###################
###############################################################################

mkdir ../f5

for i in `seq 1 50`
do 
	../cgp ../testfiles/f5.txt ../testfiles/func.txt -r 1 -c 32 -g 12 -t 0.025 -l 32 >> ../f5/test$i.txt 2> ../f5/result$i.txt
done

mkdir ../f5_coev

for i in `seq 1 50`
do 
	../coecgp ../testfiles/f5.txt ../testfiles/func.txt -r 1 -c 32 -g 12 -t 0.025 -l 32 -a 2 -p 3 -s 16 -cg 32 -b 8 -ch 16   >> ../f5_coev/test$i.txt 2> ../f5_coev/result$i.txt
done
