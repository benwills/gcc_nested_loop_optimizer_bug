#!/bin/bash


SRC_FILENAME=nestedLoopBugMaybe.c
BIN_CC="gcc-12"
BIN="nestedLoopBugMaybe"

opt_level=( 0 1 2 3 )
for i in "${opt_level[@]}"
do
	$BIN_CC $SRC_FILENAME -o $BIN -O$i
	./$BIN > output.O$i.txt
done
