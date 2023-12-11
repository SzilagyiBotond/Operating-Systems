#! /bin/bash


F=""
if [ $# -eq 0 ];then
echo "Not okay lil bro"
exit 1
fi
found=false
while ! $found;do
found=true
read -p "What is the file: ": file
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
echo "The arguments: $@"
echo "The files: $F"
