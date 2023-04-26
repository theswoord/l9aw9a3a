
SRC = get_next_line.c get_next_line_utils.c
NAME = gnl.a
CC = gcc
CFLAGS= -Wall -Wextra -Werror
msa7 = rm -rf
obj = ${SRC:.c=.o}

.SILENT:
all: ${NAME}

${NAME} : ${obj}
	ar rcs ${NAME} ${obj}
clean : 
	${msa7} ${obj}

fclean : clean
	${msa7} ${NAME}

re : fclean all