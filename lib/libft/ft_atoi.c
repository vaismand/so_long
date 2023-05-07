/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:27:45 by dvaisman          #+#    #+#             */
/*   Updated: 2022/10/03 13:45:15 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' 
	|| c == '\v' || c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	size_t			i;
	int				sign;
	unsigned int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > 2147483647 && sign == 1)
		return (-1);
	if (result > 2147483648 && sign == -1)
		return (0);
	return (result * sign);
}

int	main(void)
{
	char n[40] = "99999999999999999999999999";
	int i1 = atoi(n);
	int i2 = ft_atoi(n);

	printf("%d", i1);
	printf("%c", '\n');
	printf("%d", i2);
	return (0);
}