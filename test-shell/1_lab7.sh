#! /bin/bash


if [ $# -eq 0 ];then
echo "No args bro"
exit 1
fi
while true;do
for a;do
echo "The number of processes run by $a: $(ps -ef|grep -c -E "$a")"
sleep 1
done
done
