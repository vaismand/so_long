/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:31:54 by dvaisman          #+#    #+#             */
/*   Updated: 2022/10/03 13:32:15 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	ft_tolower(unsigned char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
