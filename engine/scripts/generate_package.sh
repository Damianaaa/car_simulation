#!/bin/bash
interface=0
tests=0
name=''
current_path=$(pwd)

while getopts n:it flag
do
    case "${flag}" in
        n) name=${OPTARG};;
        i) interface=1;;
        t) tests=1;;
    esac
done

if [[ -z $name ]]
then
    echo "Cannot create package with empty name"
    exit
fi

echo "Creating package $name ..."

mkdir $name $name/src $name/hdr
if [[ tests -eq 1 ]]
then
    mkdir $name/test
    touch $name/test/"${name}_test.cpp"
    touch $name/test/BUILD
fi

touch $name/BUILD
touch $name/hdr/"${name}.h"
if [[ interface -eq 0 ]]
then
    touch $name/src/"${name}.cpp"
fi

