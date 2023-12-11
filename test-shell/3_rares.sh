#! /bin/bash

read -p "What is the directory: " directory

if [ ! -d $directory ];then
echo $a is not a directory
exit 1
fi

for a in $(find $directory | grep -E "\.log");do
grep -q -E "" $a | sort >> save.log
rm $a
mv -T save.log $a
done
