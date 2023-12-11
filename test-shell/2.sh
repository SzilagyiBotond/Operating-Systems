#! /bin/bash

if [ $# -ne 1 ];then
echo "Only 1 argument is needed for this script"
exit 1
fi

if [ ! -d $1 ];then
echo "THe input is not a directory"
exit 1
fi

if [ -d $1 ];then
for files in $(find $1);do
if [ -f $file ];then
if file $files |grep -q -E "C source";then
echo "$files"
fi
fi
done
fi
