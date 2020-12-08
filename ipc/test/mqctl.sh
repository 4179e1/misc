#!/bin/bash - 
export PATH=../:$PATH
OBJ=/test1
mqctl create $OBJ
mqctl attr $OBJ
mqctl send $OBJ 100 9999
mqctl send $OBJ 100 6
mqctl attr $OBJ
mqctl send $OBJ 50 18
mqctl attr $OBJ
mqctl send $OBJ 33 18
mqctl attr $OBJ
mqctl recv $OBJ
mqctl attr $OBJ
mqctl recv $OBJ
mqctl attr $OBJ
mqctl recv $OBJ
mqctl attr $OBJ
mqctl recv $OBJ
mqctl attr $OBJ
mqctl recv -n $OBJ	#non-block
mqctl notify $OBJ &
mqctl send $OBJ 33 18
kill %1
mqctl unlink $OBJ
