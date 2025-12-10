#!/bin/bash
num=15
if [ $num -gt 10 ] && [ $num -lt 20 ]; then
    echo "$num 在 10 到 20 之间"
else
    echo "$num 不在 10 到 20 之间"
fi