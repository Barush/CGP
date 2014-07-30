#!/bin/bash

files=./test*

for i in $files
do
	`cat $i | tail -1`
done

