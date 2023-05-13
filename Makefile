CFLAGS  = -Wall -Wextra -Werror
NAME    = so_long
OBJS    = ${SRCS:.c=.o}
CC              = cc
RM              = rm -f
SRCS    = so_long.c

RED= \033[0;91m
GREEN= \033[1;92m
BLUE= \033[0;94m

all: ${NAME}
	@echo "${GREEN}Compilation done!"

${NAME}: ${OBJS}
	@${MAKE} -s -C ./mlx-linux
	@${CC} ${CFLAGS} -g ${OBJS} -L./mlx_linux -lXext -lX11 -lm -lz -o ${NAME} ./mlx-linux/libmlx.a

${OBJS}:
	@${CC} ${CFLAGS} -I/usr/include -Imlx-linux -O3 -c ${SRCS}

fclean: clean
	@${RM} ${NAME}
	@echo "${BLUE}Cleaning is done!"

clean:
	@${MAKE} clean -s -C ./mlx-linux
	@${RM} ${OBJS}

re: fclean all

bonus: all

norm:
	norminette -R CheckForbiddenSourceHeader */*.[ch]

.PHONY: all clean fclean re norm .c.o