



SRC = helpers.c main.c lexer.c lexic_utils.c memory_friend.c ./builtins/cd.c ./builtins/echo.c ./builtins/env.c ./builtins/executable.c ./builtins/exit.c ./builtins/export.c ./builtins/helpers0.c ./builtins/pipes.c ./builtins/redi.c ./builtins/unset.c ./builtins/errors/exit_status.c ./builtins/pwd.c ./builtins/heredoc.c ./tools1.c ./tools2.c ./sequence.c ./expand.c ./environ.c ./expand2.c tools0.c tokens.c lists.c lists1.c ./builtins/executable_help.c ./builtins/free_pipes.c ./builtins/redirections.c
NAME = minishell
CC = gcc

CFLAGS= -Wall -Wextra -Werror -lreadline -g -fsanitize=address
msa7 = rm -rf
obj = ${SRC:.c=.o}
objb = ${SRCB:.c=.o}

# readflag = -L/Users/zbenaiss/.brew/opt/readline/lib 
# readinc = -I/Users/zbenaiss/.brew/opt/readline/include/
readflagnbl = -L/Users/nbouhali/.brew/opt/readline/lib 
readincnbl = -I/Users/nbouhali/.brew/opt/readline/include/

# tarzan = -L$(shell brew --prefix readline)
libraries = ./printf/libftprintf.a ./gnl/gnl.a ./libft/libft.a ./ft_malloc/ft_malloc.a
SUBDIRS = gnl printf libft ft_malloc

.SILENT:
all : libs ${NAME}

${NAME} : ${obj}
	${CC} ${readflagnbl} ${CFLAGS}  ${readinc} ${obj} -lreadline $(libraries) -o $(NAME)

%.o: %.c
	${CC} -I ~/.brew/opt/readline/include/ -Wall -Wextra -Werror  -c $< -o $@

libs: $(SUBDIRS)
	# @echo "\033[1;32mmaking the libs ...\033[0m"

	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) all;)
	# @echo "\033[1;31mit's made \033[0m"
libsre: $(SUBDIRS)
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) re;)
libsclean:	$(SUBDIRS)
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) fclean;)

bonus: ${objb}
	${CC} ${CFLAGS} ${objb} $(libraries) -o $(NAMEB)

rebonus : fcleanbonus bonus

clean : 
	${msa7} ${obj}
cleanbonus : 
	${msa7} ${objb}

fclean : clean
	${msa7} ${NAME}
fcleanbonus : cleanbonus
	${msa7} ${NAMEB}

re : fclean all
