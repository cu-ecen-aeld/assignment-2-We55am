#!/bin/bash
filepath=$1
writestr=$2

if [ $# -eq 2 ]
then
    if [ -w $1 ]
    then
        echo ${writestr} > ${filepath}
        exit 1
    else
        echo "$1 doesn't exist"
        echo "Making a new Directory"
        DIR_PATH=$(dirname "$filepath")
        mkdir -p ${DIR_PATH}
        echo ${writestr} > ${filepath}
        exit 1
    fi
else
    echo "Bad arguments"
    echo "$0 <File Path> <string>"
    exit 1
fi