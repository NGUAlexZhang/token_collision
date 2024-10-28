#!/bin/bash

# 检查是否提供了文件名
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 filename"
    exit 1
fi

# 检查文件是否存在
if [ ! -f "$1" ]; then
    echo "File not found!"
    exit 1
fi

# 排序并处理文件
# sort -k2,2nr 表示根据第二列数字降序排序
# cut -d ' ' -f1 删除第二列，只保留第一列
sort -k2,2nr "$1" | cut -d ' ' -f1 > "$1.sorted"

# 将排序后的临时文件覆盖原文件
mv "$1.sorted" "$1"