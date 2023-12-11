#! /bin/bash

for a;do
if [ -f $a ];then
echo "The size of $a is: $(du -h $a| awk '{print $1}')"
fi
done
