#! /bin/bash

if [ $# -eq 0 ]; then
echo "Lil bro cant write arguments"
exit 1
fi

for a;do
if file $a|grep -q -E "text";then
head -1 $a >> out
fi
done
