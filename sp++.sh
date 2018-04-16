#!/bin/bash
make clobber
make


cd sam_folder
file=$1  # retain the part after the last slash
exts=$2
if [ -f $file.asm ]; then
   rm $file.asm
   rm $file.lis
   echo "removing old test case"
fi
cd ..
#/////////////////////////////////

if [[ "$#" -ne "2" ]] ; then
	./csc testCases/$1
	cd testCases/

	if [ -f $file.asm ]; then
	cp $file.asm ../sam_folder
	echo "copying file to folder"
	fi
	cd ../sam_folder
fi

if [[ "$2" == "-b" ]] ; then
	./csc testCases/betaTests/$1
	cd testCases/betaTests/
	ls
	if [ -f $file.asm ]; then

	cp $file.asm ../../sam_folder
	echo "copying file to folder"
	fi
	cd ../../sam_folder
fi



make
./sam $file
./macc $file
