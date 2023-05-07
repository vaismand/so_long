#include "libft.h"
#include <stdio.h>
#include "ft_memcpy.c"
#include "ft_strlen.c"
#include "ft_strdup.c"
#include "ft_strchr.c"

char	*ft_strtrim(char const *s1, char const *set)
{
    char	*str;
    size_t	i;
    size_t	j;
    size_t	len;

    if (!s1 || !set)
        return (NULL);
    i = 0;
    j = 0;
    len = ft_strlen((char *)s1);
    while (s1[i] && ft_strchr(set, s1[i]))
        i++;
    while (len > i && ft_strchr(set, s1[len - 1]))
        len--;
    str = (char *)malloc(sizeof(char) * (len - i + 1));
    if (!str)
        return (NULL);
    while (i < len)
        str[j++] = s1[i++];
    str[j] = '\0';
    return (str);
}

int main(void)
{
    char *str = ft_strtrim("aaaaa", "a");
    printf("%s", str);
}