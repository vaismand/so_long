#include "libft.h"
#include <stdio.h>

int	main(void)
{
	char *str = "  \t \v  \f  \r -12345";
	int result = ft_atoi(str);
	printf("%d", result);
	return (0);
}