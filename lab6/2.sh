#! /bin/bash
cd ..
if [ $# -ne 1 ];then
	exit 1
fi
if [ ! -d "$1" ]; then
	exit 1
fi
if [ -d "$1" ]; then

	cd $1
	for a in $(find "$1"); do
		if [ -f "$a" ]; then
			if file $1 | grep -E -q "C source"; then
				echo $a
			fi
		fi
	done
fi
cd ..
cd lab6
