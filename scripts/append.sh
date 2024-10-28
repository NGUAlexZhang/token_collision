#!/bin/bash

# 检查是否提供了文件名
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filename1> <filename2> "
    exit 1
fi

# 检查文件是否存在
if [ ! -f "$1" ]; then
    echo "$1 File not found!"
    exit 1
fi

if [ ! -f "$2" ]; then
    echo "$2 File not found!"
    exit 1
fi


# 处理文件，每一行与其他每一行拼接
while read -r line1; do
    while read -r line2; do
        echo "${line1}${line2}"
    done < "$2"
done < "$1"
