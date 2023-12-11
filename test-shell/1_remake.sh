#! /bin/bash

if [ $# -lt 1 ];then
echo Too few arguments
exit 1
fi 
for a;do
if [ -f $a ];then
du -b $a
fi
done
