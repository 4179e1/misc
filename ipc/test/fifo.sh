#!/bin/bash - 
IFILE=autumn.txt
OFILE=trash

../fifo_serv 2>/dev/null &
echo $IFILE | ../fifo_cli > $OFILE
diff -qs $IFILE $OFILE
rm -rf $OFILE
kill %1
