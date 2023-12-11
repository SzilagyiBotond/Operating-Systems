#! /bin/bash

count=0;
all=0;

for a in $(find);do
if [ -f $a ];then
count=`expr $count + 1`
if file $a | grep -E -q "\.txt" ;then
all=`expr $all + 1`
fi
fi
done
echo $all
echo $count
echo `expr $count / $all`
