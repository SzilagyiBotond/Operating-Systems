#! /bin/bash

for a; do
	if [ -f "$a" ]; then
	#ls -l $a | awk '{print $5}'
	du -h $a
	fi
done

#while [ $# -gt 0 ]; do
#	echo $1
#	shift
#done
