#!/bin/bash
filesdir=$1
searchstr=$2

if [ $# -eq 2 ]
then
    if [ -d $1 ]
    then
        X=$(find ${filesdir} -type f | wc -l)
        Y=$(grep -r ${searchstr} ${filesdir} | wc -l)
        echo "The number of files are ${X} and the number of matching lines are ${Y}"
        exit 0
    else
        echo "$1 is not a directory"
        exit 1
    fi
else
    echo "Bad arguments"
    echo "$0 <directory> <string>"
    exit 1
fi