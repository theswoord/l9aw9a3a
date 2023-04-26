



SRC = print.c ft_putchar.c ft_putnbr.c ft_putstr.c ft_unsigned.c ft_pointer.c
NAME = libftprintf.a
CC = gcc
CFLAGS= -Wall -Wextra -Werror
msa7 = rm -rf
obj = ${SRC:.c=.o}

.SILENT:
all : ${NAME}

${NAME} : ${obj}
	ar rcs ${NAME} ${obj}

clean : 
	${msa7} ${obj}

fclean : clean
	${msa7} ${NAME}

re : fclean all