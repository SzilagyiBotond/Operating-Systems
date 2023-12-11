#! /bin/bash

for a in $(cat who.fake| awk '{print $1}');do
echo "$(cat ps.fake | grep -E -v "UID"| grep -E "^[^ ]" | awk '{print $1}'| sort | uniq -c | grep -E "$a" )"
done
