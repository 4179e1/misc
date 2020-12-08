awk -F '=' '/xmhost/ $1~/'"$2"'/{print $2}'
