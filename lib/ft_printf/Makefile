.SILENT:

LIBFT     = libft
LIBFT_DIR = ../libft
LIBFT_LIB = libft.a
SRCS      = ft_printf.c \
            ft_printf_utils.c \
            ft_printf_hex.c \
            ft_printf_uns.c \
            ft_printf_ptr.c

OBJS      = ${SRCS:.c=.o}
NAME      = libftprintf.a
LIBC      = ar -rcs
RM        = rm -f
CFLAGS    = -Wall -Wextra -Werror
INCS      = .
COMPILER  = gcc -no-pie

.c.o:
	@${COMPILER} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCS}

${NAME}: ${OBJS}
	@make all -C ${LIBFT_DIR} > /dev/null
	@cp ${LIBFT_DIR}/${LIBFT_LIB} ${NAME} > /dev/null
	@${LIBC} ${NAME} ${OBJS}

all: ${NAME}

fclean: clean
	@${RM} ${NAME} ${bonus} > /dev/null
	@make fclean -C ${LIBFT_DIR}

clean:
	@${RM} -f ${OBJS} ${OBJS_B}
	@make clean -C ${LIBFT_DIR}

re: fclean all

.PHONY: all clean fclean re norm
