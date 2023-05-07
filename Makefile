.SILENT:

NAME = so_long
OBJ = ${SRCS:.c=.o}
SRC =	src/test.c
CC              = gcc -g -no-pie
RM              = rm -f
CFLAGS  = -Wall -Wextra -Werror
MINILIBX_FLAGS		= -Lmlx -lmlx OpenGL AppKit

RED= \033[0;91m
GREEN= \033[1;92m
BLUE= \033[0;94m

all: ${NAME}
	@echo "${GREEN}Compilation done!"

${NAME}: ${OBJ}
	$(CC) $(OBJ) $(MINILIBX_FLAGS) -o $(NAME)

clean:
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}
	@echo "${BLUE}Clean done!"

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader */*.[ch]

.PHONY: all clean fclean re norm .c.o