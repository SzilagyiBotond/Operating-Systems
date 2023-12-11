#! /bin/bash


if [ $# -lt 1 ];then
echo too few args
exit 1
fi 

while true;do
for a;do
ps -ef | grep -E -c "$a"
sleep 1
done
done
