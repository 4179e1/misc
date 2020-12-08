changequote(<,>)dnl
syscmd(<date --iso-8601|sed 's/-/./g'>)dnl
changequote`'dnl
define(`A', `abc')A

syscmd(`echo "define(\`AUTHOR', \`Orwell')"')dnl
AUTHOR

esyscmd(`echo "define(\`AUTHOR', \`Orwell')dnl"')dnl
AUTHOR

sysval
esyscmd(`ls /no-dir/ >/dev/null 2>&1')dnl
sysval

define(`FILENAME', mkstemp(`/tmp/myscriptXXXXXX'))dnl
FILENAME
