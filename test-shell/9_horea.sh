#9. Write a script that extracts from all the C source files given as command line arguments the included libraries and s#aves them in a file.(use the file command to check if a file is a C source file)
#Scrieti un script care extrage bibliotecile incluse din toate fisierele sursa C date ca argumente la linia de comanda si le salveaza intr-un alt fisier. (verificati cu comanda file daca un fisier este sursa C)
#! /bin/bash

for a;do
if file $a | grep -E -q "C source";then
cat $a | grep -E "#include" | awk '{print $2}' >> outC
fi
done

