#!/bin/bash
make
./csc $1
cd sam_folder
file=${1##*/}  # retain the part after the last slash
if [ -f $file.asm ]; then
   rm $file.asm
   rm $file.lis
   echo "removing old test case"
fi
cd ..
cd "${1%/*}"
if [ -f $file.asm ]; then
cp $file.asm ../sam_folder
echo "copying file to folder"
fi
cd ../sam_folder
make
./sam $file
./macc $file
