set -o noclobber
echo abc >|$$
echo def >$$
cat $$
set +o noclobber

rm -rf $$
