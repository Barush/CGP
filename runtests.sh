#!/bin/sh

for i in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
do
	echo "Run $i:"
	time -o time$i.txt ./cocgp testdata.txt >> nightTest$i.txt
done