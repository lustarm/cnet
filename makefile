OBJS = $(wildcard src/*.c)
NAME = cnet

CC = gcc
CCFLAGS = -Wall -Wextra
CCDEFINES = -DDEBUG -DLOG_USE_COLOR

all : $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o build/$(NAME) $(CCDEFINES)

