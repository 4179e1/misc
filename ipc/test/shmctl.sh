#!/bin/bash - 
export PATH=../:$PATH
OBJ=/shmtest1
LENGTH=16384
shmctl create $OBJ $LENGTH
shmctl write $OBJ
shmctl read $OBJ
shmctl unlink $OBJ
