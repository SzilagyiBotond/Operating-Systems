#! /bin/bash

read -p "What is the directory: " directory 

if [ ! -d $directory ];then
echo $directory IS NOT A DIRECTORY
exit 1
fi

for a in $(find $directory);do
if [ -L $a ];then
if [ ! -e $a ];then
echo $a
fi
fi
done
