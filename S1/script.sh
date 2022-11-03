#!/usr/bin/bash
start=$(pwd)
cd "$1"

if [ -f "Makefile" ]; then
    make clean
fi

cd "$start"
date --rfc-3339 'seconds' > "manifest.txt"
# count number of line in all .c and .h files without writing the file names
find $1 -name "*.c" -o -name "*.h" -o -name "*.py" | xargs wc -l | tail -n 1 | awk '{ print $1 }' >> "manifest.txt"
cd "$1"

echo "$(id -un)@$(hostname)" >> "$start/manifest.txt"
cd "$start"
tar -cJf  "$1".tar.xz manifest.txt "$1" 
rm manifest.txt