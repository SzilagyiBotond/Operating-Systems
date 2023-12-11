#! /bin/bash

while [ ! -f $file ] || [ -z $file ];do
read -p "What is the file: " file
done
res=""
for a in $(cat $file);do
f=""
f="$f$a"
f+="@scs.ubbcluj.ro"
res="$res$f"
res+=","
done
echo $res
res2=${res::-1}
echo $res2
