/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_so_long.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:51:53 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/24 15:45:35 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*ft_get_line(t_gnl gnl, char *left_str, t_game *game)
{
	gnl.i = 0;
	if (!left_str[gnl.i])
		return (NULL);
	while (left_str[gnl.i] && left_str[gnl.i] != '\n')
		gnl.i++;
	gnl.str = (char *)malloc(sizeof(char) * (gnl.i + 2));
	if (!gnl.str)
	{
		free(left_str);
		ft_error_msg("Malloc error\n", game);
	}
	gnl.i = 0;
	while (left_str[gnl.i] && left_str[gnl.i] != '\n')
	{
		gnl.str[gnl.i] = left_str[gnl.i];
		gnl.i++;
	}
	if (left_str[gnl.i] == '\n')
		gnl.str[gnl.i] = left_str[gnl.i];
	gnl.str[gnl.i] = '\0';
	return (gnl.str);
}

static char	*ft_new_left_str(t_gnl gnl, char *left_str, t_game *game)
{
	gnl.i = 0;
	while (left_str[gnl.i] && left_str[gnl.i] != '\n')
		gnl.i++;
	if (!left_str[gnl.i])
	{
		free(left_str);
		return (NULL);
	}
	gnl.str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - gnl.i + 1));
	if (!gnl.str)
	{
		free(left_str);
		free(gnl.line);
		ft_error_msg("Malloc error\n", game);
	}
	gnl.i++;
	gnl.j = 0;
	while (left_str[gnl.i])
		gnl.str[gnl.j++] = left_str[gnl.i++];
	gnl.str[gnl.j] = '\0';
	free(left_str);
	return (gnl.str);
}

static char	*ft_read_to_left_str(t_gnl gnl, char *left_str, t_game *game)
{
	gnl.buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!gnl.buff)
	{
		free(left_str);
		ft_error_msg("Malloc error\n", game);
	}
	gnl.rd = 1;
	while (!ft_strchr(left_str, '\n') && gnl.rd > 0)
	{
		gnl.rd = read(gnl.fd, gnl.buff, BUFFER_SIZE);
		if (gnl.rd < 0)
		{
			free(left_str);
			free(gnl.buff);
			ft_error_msg("Error reading file\n", game);
		}
		if (gnl.rd == 0)
			break ;
		gnl.buff[gnl.rd] = '\0';
		left_str = gnl_strjoin(left_str, gnl, game);
	}
	free(gnl.buff);
	return (left_str);
}

char	*get_next_line(t_gnl gnl, int fd, t_game *game)
{
	static char	*left_str;

	gnl.fd = fd;
	if (gnl.fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str = ft_read_to_left_str(gnl, left_str, game);
	if (!left_str)
		return (NULL);
	gnl.line = ft_get_line(gnl, left_str, game);
	if (!gnl.line)
	{
		free(left_str);
		left_str = NULL;
		ft_error_msg("Malloc error\n", game);
	}
	left_str = ft_new_left_str(gnl, left_str, game);
	if (!left_str)
	{
		free(left_str);
		left_str = NULL;
	}
	return (gnl.line);
}

void	ft_fill_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	game->fd = open(game->map.file, O_RDONLY);
	if (game->fd < 0)
		ft_error_msg("Error opening map\n", game);
	while (1)
	{
		game->line = get_next_line(game->gnl, game->fd, game);
		if (game->line == 0)
			break ;
		j = -1;
		while (++j < game->map.columns)
			game->map.full[i][j] = game->line[j];
		free(game->line);
		i++;
	}
	if (close(game->fd) < 0)
		ft_error_msg("Error closing map\n", game);
}
