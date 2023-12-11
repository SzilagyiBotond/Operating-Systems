#! /bin/bash

if [ $# -ne 1 ];then
echo Too many arguments
exit 1
fi

if [ ! -d $1 ];then
echo Argument is not directory
exit 1
fi

for a in $(find $1);do
if file $a|grep -E -q "C source";then
echo $a
fi
done
