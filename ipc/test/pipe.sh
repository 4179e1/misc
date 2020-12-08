#!/bin/bash - 
IFILE=autumn.txt
OFILE=trash
echo $IFILE | ../pipe > $OFILE
diff -qs $IFILE $OFILE
echo $IFILE | ../pipe > $OFILE
diff -qs $IFILE $OFILE
rm -rf $OFILE
