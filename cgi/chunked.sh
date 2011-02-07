#!/bin/bash
echo -e -n "Transfer-Encoding: chunked\r\n"
echo  -e -n "Content-type: text/html\r\n"

#add an empty line between header and message
echo -e -n "\r\n"

echo -e -n "b\r\nhelloworld!\r\n"
echo -e -n "3\r\nabc\r\n"
echo -e -n "0\r\n"
#add an empty line to terminal the chunked transfer
echo -e -n "\r\n"
