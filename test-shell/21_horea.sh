#! /bin/bash

read -p "What is the directory: " directory

if [ ! -d $directory ];then
echo "Not a directory"
exit 1
fi
for a in $(find $directory);do
if [ -f $a ];then
size=$(du -h $a| cut -f1)
permissions=$(ls -l $a|cut -d" " -f1)
unique=$(cat $a|sort | uniq | wc -l)
echo "Name: $(find $a| awk -F/ '{print $NF}') Size: $size Permissions: $permissions Unique: $unique"
fi
done
