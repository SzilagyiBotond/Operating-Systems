#! /bin/bash

read -p "What is the directory: " directory

if [ ! -d $directory ];then
echo "$directory is not a directory"
exit 1
fi

count=0

for a in $(find $directory| grep -E "\.c");do
if [ -f $a ];then
if [ $(grep -E -c "." $a) -gt 500 ];then
count=`expr $count + 1`
if [ $count -gt 2 ];then
break
fi
echo $a
fi
fi

done

