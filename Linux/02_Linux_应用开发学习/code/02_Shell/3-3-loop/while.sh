#!/bin/bash
sum=0
i=1
while [ $i -le 10 ]; do
    sum=$((sum + i))
    i=$((i + 1))
done
echo "1到10的累加和是：$sum"
