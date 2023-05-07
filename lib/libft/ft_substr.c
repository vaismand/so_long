#include "libft.h"
#include "ft_strlen.c"
#include "ft_strdup.c"
#include <stdio.h>

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char	*str;
    size_t  length;
    size_t	i;

    if (!s)
        return (NULL);
    length = ft_strlen((char *)s);
    if (start > length)
        return (ft_strdup(""));
    if (length - start < len)
        len = length - start;
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (i < len)
    {
        str[i] = s[start + i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

int	main(void)
{
    char	str[10] = "123456789";
    printf("%s", ft_substr(str, 3, 5));
    return (0);
}