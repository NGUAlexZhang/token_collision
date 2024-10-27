#!/bin/bash

# 检查是否有文件名作为参数
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 filename"
    exit 1
fi

# 使用awk来处理文件，只保留每行的第一个字段
awk '{print $1}' "$1"