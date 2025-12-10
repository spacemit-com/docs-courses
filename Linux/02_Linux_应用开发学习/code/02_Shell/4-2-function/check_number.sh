#!/bin/bash
check_number() {
    if [ $1 -gt 10 ]; then
        return 0
    else
        return 1
    fi
}

check_number 15
if [ $? -eq 0 ]; then
    echo "数字大于10"
else
    echo "数字小于等于10"
fi
