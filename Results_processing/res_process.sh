#!/bin/bash

#funcs=(../sums_coev ../sums_coev_16)
funcs=(../sinx_ex ../sinx_ex_coev)

for func in ${funcs[*]}
#for all generation counts
do
	fit=""
	generation=""
	files=$func/test*
	for i in $files
	do
		fit="$fit `cat $i | tail -1 |  cut -d' ' -f2`"
		generation="$generation `cat $i | tail -1 |  cut -d' ' -f1`"
	done
	echo $fit >> fitness.data
	echo $generation >> generation.data

	counted=""
	timing=""
	files=$func/result*
	for i in $files
	do
		counted="$counted `cat $i | grep Counted | cut -d' ' -f3`"
		timing="$timing `cat $i | grep CPU | cut -d' ' -f4`"
	done
	echo $counted >> counted.data
	echo $timing >> timing.data
done

Rscript ./draw_plots.r success_rate.pdf fitness.data "" "Výsledná fitness"
rm fitness.data

Rscript ./draw_plots.r generation_count.pdf generation.data "" "Počet generací"
rm generation.data

Rscript ./draw_plots.r counted_nodes.pdf counted.data "" "Počet vyčíslených datových bodů"
rm counted.data

Rscript ./draw_plots.r count_time.pdf timing.data "" "Čas výpočtu [s]"
rm timing.data