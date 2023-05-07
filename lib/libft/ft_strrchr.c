/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:01:58 by dvaisman          #+#    #+#             */
/*   Updated: 2022/10/03 14:03:16 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last = (char *)s;
		s++;
	}
	if (last)
		return (last);
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

int	main(void)
{
	char	str[10] = "1253456789";
	char	*ptr;
	ptr = ft_strrchr(str, '5');
	printf("%s", ptr);
	return (0);
}
