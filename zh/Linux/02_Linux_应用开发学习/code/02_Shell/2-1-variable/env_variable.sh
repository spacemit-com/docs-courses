#!/bin/bash
# 备份原PATH变量值
old_path=$PATH
echo "old path: $old_path"
# 添加新路径到PATH变量
PATH=$PATH:/new/path
echo "new path: $PATH"
# 恢复原PATH变量值
PATH=$old_path
