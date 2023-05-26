CFLAGS    = -Wall -Wextra -Werror
NAME      = so_long
SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)
CC        = gcc
RM        = rm -f
LIBFT     = ./lib/libft/libft.a
FT_PRINTF = ./lib/ft_printf/libftprintf.a
MLX_DIR   = ./mlx-linux
MLX_LIB   = $(MLX_DIR)/libmlx.a
MLX_INC   = -I$(MLX_DIR)

RED       = \033[0;91m
GREEN     = \033[1;92m
BLUE      = \033[0;94m

all: ${NAME}

${NAME}: ${OBJS}
	@${MAKE} -s -C ./lib/libft > /dev/null
	@${MAKE} -s -C ./lib/ft_printf > /dev/null
	@${MAKE} -s -C $(MLX_DIR) > /dev/null
	@${CC} ${CFLAGS} ${OBJS} -L$(MLX_DIR) ${MLX_INC} -lmlx -lXext -lX11 -lm -lz -o ${NAME} ${LIBFT} ${FT_PRINTF} > /dev/null
	@echo "${GREEN}Compilation is done!"

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${MLX_INC}

fclean: clean
	@${RM} ${NAME}
	@echo "${BLUE}Cleaning is done!"

clean:
	@${MAKE} clean -s -C $(MLX_DIR)
	@${MAKE} clean -s -C ./lib/libft
	@${MAKE} clean -s -C ./lib/ft_printf
	@${RM} ${OBJS}

re: fclean all

bonus: all

norm:
	norminette -R CheckForbiddenSourceHeader */*.[ch]

.PHONY: all clean fclean re norm .c.o