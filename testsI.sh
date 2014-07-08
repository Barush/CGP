#!/bin/sh



###############################################################################
############################  e^abs(x) * sin(x)  ##############################
###############################################################################

mkdir salustowitz

for i in `seq 5 50`
do 
	./cgp testfiles/salustowitz.txt func.txt -r 1 -c 32 -g 12 -t 0.025 -l 32 >> salustowitz/test$i.txt 2> salustowitz/result$i.txt
done

#mkdir sums

#for i in `seq 1 50`
#do 
#	./cgp testfiles/sums.txt func.txt -r 1 -c 32 -g 12 -t 1.5 -l 32 -p 3 -s 16 -cg 32 -b 8 -ch 16   >> sums/test$i.txt 2> sums/result$i.txt
#done

