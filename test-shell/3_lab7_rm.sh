#! /bin/bash

touch out

for a;do
if file $a | grep -E -q "text";then
head -1 $a >> out
fi
done
