#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
cd $DIR

function check()
{
    for f in $(find tests/$1 -type f -name "*.lat")
    do
        echo "$f:"
        ./latc_x86 $f >> /dev/null
        if [[ $? -eq $2 ]] ; then
            echo -e "\033[31mERROR!\e[0m"
        else
            echo -e "\e[92mOK!\e[0m"
        fi
    done
}

echo "BAD TESTS CHECK:"
check "bad" 0

echo -e "\n\nCORE TESTS CHECK:"
check "good" 1

echo -e "\n\nEXTENSIONS TESTS CHECK:"
check "extensions" 1
