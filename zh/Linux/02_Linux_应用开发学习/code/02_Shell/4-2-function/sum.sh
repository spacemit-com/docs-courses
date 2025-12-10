#!/bin/bash
sum() {
    result=$(( $1 + $2 ))
    echo "两数之和为：$result"
}

# 调用函数并传递参数
sum 5 3
