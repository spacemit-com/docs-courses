#!/bin/bash
str="Hello, world!"
sub_str="world"
if echo "$str" | grep -q "$sub_str"; then
    echo "包含子字符串$sub_str"
else
    echo "不包含子字符串$sub_str"
fi