#!/bin/bash
echo "请输入选项：1. 查看目录 2. 创建文件 3. 退出"
read choice
case $choice in
1)
    ls
    ;;
2)
    touch new_file.txt
    echo "创建了文件 new_file.txt"
    ;;
3)
    echo "退出程序"
    exit 0
    ;;
*)
    echo "无效的选项"
    ;;
esac