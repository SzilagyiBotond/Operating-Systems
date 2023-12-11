#! /bin/bash

read -p "What is the directory: " directory

if [ ! -d $directory ];then
echo "This is not a directory"
exit 1
fi

F=""
for a in $(find $directory);do
if file $a | grep -E -q "C source";then
rm $a
fi
done
for a in $(find $directory);do
if [ -f $a ];then
echo $a >> out_horea
fi
done
cat out_horea | sort
