#! /bin/bash

read -p "What is the directory: " direc

if [ ! -d $direc ];then
echo $direc is not a directory
exit 1
fi 

for a in $(find $direc);do
if [ -f $a ];then
if [ $(ls -l $a|awk '{print $1}'|grep -E -o "r"| wc -l) -gt 2 ];then
ls -l $a
chmod -w $a
ls -l $a
fi
fi
done
