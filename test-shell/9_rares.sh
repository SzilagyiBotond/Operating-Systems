#! /bin/bash

read -p "WHat is the directory: " direc

if [ ! -d $direc ];then
echo "Bro this is not a directory"
exit 1
fi
for a in $(find $direc| grep -E -v "Identifier$");do
if [ -f $a ];then
for b in $(find $direc| grep -E -v "Identifier$");do
if [ -f $b ];then
if [ $a != $b ];then
if [ "$(md5sum $a | awk -F" " '{print $1}')" == "$(md5sum $b| awk -F" " '{print $1}')" ];then
echo "$a - $b"
fi
fi
fi
done
fi
done
#for a in $(find $direc);do
#if [ -f $a ];then
#for b in $(find $direc);do
#if [ -f $b ];then
#if [ $a != $b ];then
#if [ "$(ls -l $a|sha1sum)" == "$(ls -l $b|sha1sum)" ];then
#echo "$a - $b"
#fi
#fi
#fi
#done
#fi
#done
