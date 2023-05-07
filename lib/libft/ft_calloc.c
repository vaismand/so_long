/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:31:14 by dvaisman          #+#    #+#             */
/*   Updated: 2022/10/05 12:35:33 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_bzero.c"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

int	main(void)
{
	char	*str;
	int		*arr;
	int		i;

	str = ft_calloc(10, sizeof(char));
	arr = ft_calloc(10, sizeof(int));
	i = 0;
	while (i < 10)
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < 10)
	{
		printf("%d", arr[i]);
		i++;
	}
	printf("\n");
	return (0);
}
