#! /bin/bash 

for a;do
if cat ps.fake| grep -E "$a" ;then
killall $a
echo $a killed
fi
done
