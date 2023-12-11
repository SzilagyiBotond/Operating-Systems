#! /bin/bash

for a in $(ls | grep -E ".txt");do
if grep -E -q "cat" $a;then
echo $a
fi
done
