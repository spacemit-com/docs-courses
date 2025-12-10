#!/bin/bash
fruits=("apple" "banana" "cherry")
echo "数组第一个元素为: ${fruits[0]}"
echo "数组全部元素为: ${fruits[*]}"
echo "数组全部元素为: ${fruits[@]}"
fruits+=("date")
echo "新增元素后数组全部元素为: ${fruits[@]}"