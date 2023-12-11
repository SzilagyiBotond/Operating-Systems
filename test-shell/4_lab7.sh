#! /bin/bash

if [ $# -eq 0 ];then
echo "Who let him cook"
exit 1
fi

if [ $# -eq 1 ];then
echo "My man ate the second argument"
exit 1
fi

while [ $# -ne 0 ];do
if [ -f $1 ];then
if [ $(grep -E -o "$2" $1|wc -l) -gt 2 ];then
echo "In $1, $2 appears more than 3 times"
fi
fi
shift 2
if [ $# -eq 1 ];then
exit 0
fi
done
