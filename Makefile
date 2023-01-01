CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
NAME = hsh

all: main.h $(OBJ)
	$(CC) $(OBJ) -o $(NAME)