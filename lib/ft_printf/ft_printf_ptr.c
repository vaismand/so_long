/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:28:39 by dvaisman          #+#    #+#             */
/*   Updated: 2022/11/09 12:28:39 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_pointer_len(unsigned	long number)
{
	int	count;

	count = 0;
	if (number == 0)
		return (1);
	while (number != 0)
	{
		number /= 16;
		count++;
	}
	return (count);
}

static int	ft_print_ptr(unsigned long long value)
{
	if (value >= 16)
	{
		ft_print_ptr(value / 16);
		ft_print_ptr(value % 16);
	}
	else
	{
		if (value <= 9)
			ft_putchar_fd(value + '0', 1);
		else
			ft_putchar_fd(value - 10 + 'a', 1);
	}
	return (ft_pointer_len(value));
}

int	ft_print_pointer(unsigned long long address)
{
	int	print_len;

	print_len = 0;
	if (!address)
	{
		write(1, "(nil)", 5);
		print_len += 5;
	}
	else
	{
		write(1, "0x", 2);
		print_len += 2;
		print_len += ft_print_ptr(address);
	}
	return (print_len);
}
