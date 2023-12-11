#! /bin/bash

count=0
wca=0

for a in $(ls | grep -E ".txt");do
count=`expr $count + 1`
wca=`expr $wca + $(cat $a|wc -l)`
done
echo `expr $wca / $count`
