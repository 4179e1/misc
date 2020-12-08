#!/bin/bash - 
export PATH=../:$PATH
OBJ=/semtest1
semctl create $OBJ
semctl getval $OBJ
semctl wait $OBJ
semctl getval $OBJ
semctl post $OBJ
semctl getval $OBJ
semctl unlink $OBJ
