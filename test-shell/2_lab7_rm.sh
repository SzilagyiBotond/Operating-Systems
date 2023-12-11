#! /bin/bash

if [ $# -lt 1 ];then
echo Too few args
exit 1
fi

found=false
F=""

while ! $found;do
found=true
read -p "File ": file
if [ -f $file ];then
F="$F $file"
for a;do
if ! grep -E -q "$a" $F;then
found=false
fi 
done
else
found=false
fi
done
