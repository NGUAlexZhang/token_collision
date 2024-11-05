#!/bin/bash

# 检查参数个数
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 file1 file2 file3"
    exit 1
fi

# 读取每个文件的所有行到数组中
mapfile -t lines1 < "$1"
mapfile -t lines2 < "$2"
mapfile -t lines3 < "$3"

for l1 in "${lines1[@]}"; do
    combo="$l1"
    [[ ${#combo} -gt 6 ]] && echo "$combo"
done
for l1 in "${lines2[@]}"; do
    combo="$l1"
    [[ ${#combo} -gt 6 ]] && echo "$combo"
done
for l1 in "${lines3[@]}"; do
    combo="$l1"
    [[ ${#combo} -gt 6 ]] && echo "$combo"
done
for l1 in "${lines1[@]}"; do
    for l2 in "${lines2[@]}"; do
        combo="$l1$l2"
        [[ ${#combo} -gt 6 ]] && echo "$combo"
        combo="$l2$l1"
        [[ ${#combo} -gt 6 ]] && echo "$combo"
    done
done
for l1 in "${lines1[@]}"; do
    for l2 in "${lines3[@]}"; do
        combo="$l1$l2"
        [[ ${#combo} -gt 6 ]] && echo "$combo"
        combo="$l2$l1"
        [[ ${#combo} -gt 6 ]] && echo "$combo"
    done
done
for l1 in "${lines3[@]}"; do
    for l2 in "${lines2[@]}"; do
        combo="$l1$l2"
        [[ ${#combo} -gt 6 ]] && echo "$combo"
        combo="$l2$l1"
        [[ ${#combo} -gt 6 ]] && echo "$combo"
    done
done
# 生成所有可能的字符串组合，并检查长度是否大于6
for l1 in "${lines1[@]}"; do
    for l2 in "${lines2[@]}"; do
        for l3 in "${lines3[@]}"; do
            # 三个字符串组合
            combo="$l1$l2$l3"
            [[ ${#combo} -gt 6 ]] && echo "$combo"
            combo="$l1$l3$l2"
            [[ ${#combo} -gt 6 ]] && echo "$combo"
            combo="$l2$l1$l3"
            [[ ${#combo} -gt 6 ]] && echo "$combo"
            combo="$l2$l3$l1"
            [[ ${#combo} -gt 6 ]] && echo "$combo"
            combo="$l3$l2$l1"
            [[ ${#combo} -gt 6 ]] && echo "$combo"
            combo="$l3$l1$l2"
            [[ ${#combo} -gt 6 ]] && echo "$combo"
        done
    done
done
