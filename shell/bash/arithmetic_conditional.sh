if [ \( 3 -gt 2 \) ];then echo ture;fi
if test $(((3 > 2) || (4 <= 1))) = 1;then echo ture;fi
if (((3 > 2) || (4 <= 1)));then echo ture;fi
