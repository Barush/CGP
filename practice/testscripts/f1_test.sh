#!/bin/sh

###############################################################################
#############  F1: 50 runs without coev, 50 runs with coev  ###################
###############################################################################

mkdir ../f1

for i in `seq 1 50`
do 
	../cgp ../testfiles/f1.txt ../testfiles/func.txt -r 1 -c 32 -g 12 -t 0.5 -l 32 >> ../f1/test$i.txt 2> ../f1/result$i.txt
done

mkdir ../f1_coev

for i in `seq 1 50`
do 
	../coecgp ../testfiles/f1.txt ../testfiles/func.txt -r 1 -c 32 -g 12 -t 0.5 -l 32 -a 2 -p 3 -s 8 -cg 32 -b 8 -ch 16   >> ../f1_coev/test$i.txt 2> ../f1_coev/result$i.txt
done
