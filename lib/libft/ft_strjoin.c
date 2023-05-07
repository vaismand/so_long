/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:26:40 by dvaisman          #+#    #+#             */
/*   Updated: 2022/10/06 10:27:42 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "ft_strlen.c"
#include "ft_memcpy.c"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_l;
	size_t	s2_l;

	if (!s1 || !s2)
		return (NULL);
	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_l + s2_l + 1));
	ft_memcpy(str, s1, s1_l);
	ft_memcpy(str + s1_l, s2, s2_l);
	str[s1_l + s2_l] = '\0';
	return (str);
	free(str);
}

int main(void)
{
	char *str1 = "12345";
	char *str2 = "67890";
	char *str3 = ft_strjoin(str1, str2);
	printf("%s", str3);
	return (0);
}