#!/bin/bash
printf "hello world\n"

printf "%s %s\n" hello world

printf "hello %s\n" world

printf "%%\n"

printf "|%10s|\n" hello
printf "|%-10s|\n" hello

intvar=123
printf "%d\n" $intvar
echo

myvar=42.123456
printf "|%*.*G|\n" 5 6 $myvar
printf "|%*.*G|\n" 6 5 $myvar
printf "|%15e|\n" $myvar
printf "|%15E|\n" $myvar
printf "|%10f|\n" $myvar
printf "|%10g|\n" $myvar
printf "|%10G|\n" $myvar
echo

printf "|% 15f|\n" $myvar
printf "|% 15f|\n" -$myvar
printf "|%+15f|\n" $myvar
printf "|%+15f|\n" -$myvar
echo

printf "%#x\n" $intvar
printf "%#e\n" $myvar
printf "%#g\n" $myvar
echo

printf "|%015f|\n" $myvar
echo

printf "%s\n" "hello\nworld"
printf "%b\n" "hello\nworld"
echo

printf "%q\n" "greetings to the world"
