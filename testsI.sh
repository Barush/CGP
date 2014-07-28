#!/bin/sh



###############################################################################
############################  e^abs(x) * sin(x)  ##############################
###############################################################################

mkdir ball

for i in `seq 30 30`
do 
	./cgp testfiles/ball_1d.txt func.txt -r 1 -c 32 -g 12 -t 0.025 -l 32 >> ball/test$i.txt 2> ball/result$i.txt
done

#mkdir sums

#for i in `seq 1 50`
#do 
#	./cgp testfiles/sums.txt func.txt -r 1 -c 32 -g 12 -t 1.5 -l 32 -p 3 -s 16 -cg 32 -b 8 -ch 16   >> sums/test$i.txt 2> sums/result$i.txt
#done

