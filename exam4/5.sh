#! /bin/bash


all=0;
current=0;

for a in $(find);do
if file $a | grep -E -q "\.sh" ;then
all=`expr $all + 1`
current=`expr $current + $(grep -E -v "^#" $a|grep -E "([^ ])"| wc -l)`
fi
done
echo `expr $current / $all`
