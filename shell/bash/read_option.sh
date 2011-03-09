read -d s aline <<EOF
alice duches bob
EOF
#output "alice duche", the remaining part is discarded.
echo $aline

read -n 5 aline <<EOF
1234567890
EOF
#output "12345"
echo $aline

read aline <<EOF
A line with a\n escape sequence
EOF
#output "A line with a escape sequence"
echo $aline

read -r aline <<EOF
A line with a\n escape sequence
EOF
#output "A line with a\n escape sequence"
echo $aline

#doesn't echo user input
echo -n "hah?"
read -s -n1 choice
echo

read -p "you have 5 seconds to make a choice" -t 5 choice
echo

read -p "what's your choice?" choice
echo $choice

