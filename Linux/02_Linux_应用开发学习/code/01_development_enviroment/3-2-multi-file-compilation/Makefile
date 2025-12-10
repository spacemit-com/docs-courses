# 定义变量
CC = gcc
CFLAGS = -Wall -g
TARGET = app

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): main.o utils.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o utils.o

# 编译源文件
main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

# 清理生成文件
clean:
	rm -f *.o $(TARGET)
