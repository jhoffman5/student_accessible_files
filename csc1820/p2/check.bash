#!/bin/bash

if [ -z "$1" ]
then
	echo "Must provide a word to look for"
else
	grep  -w $1 words.txt | wc -w
fi