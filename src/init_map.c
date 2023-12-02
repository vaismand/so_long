/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:33 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/24 15:31:47 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_rectangular(t_game *game)
{
	int		i;

	i = 0;
	game->fd = open(game->map.file, O_RDONLY);
	if (game->fd < 0)
		ft_error_msg("Error opening map\n", game);
	while (1)
	{
		game->line = get_next_line(game->gnl, game->fd, game);
		if (game->line == 0)
			break ;
		else
		{
			if ((int)ft_strlen(game->line) != game->map.columns)
				i++;
			free(game->line);
		}
	}
	if (close(game->fd) < 0)
		ft_error_msg("Error closing map\n", game);
	if (i > 0)
		return (1);
	return (0);
}

int	ft_render_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.rows)
	{
		j = -1;
		while (++j < game->map.columns)
		{
			if (game->map.full[i][j] == '1')
				ft_render_img(game, game->img[0], j, i);
			else if (game->map.full[i][j] == 'C')
				ft_render_img(game, game->img[6], j, i);
			else if (game->map.full[i][j] == 'E' && game->map.chests == 0)
				ft_render_img(game, game->img[4], j, i);
			else if (game->map.full[i][j] == 'E' && game->map.chests > 0)
				ft_render_img(game, game->img[5], j, i);
			else if (game->map.full[i][j] == 'P')
				ft_render_player(game, j, i, game->player_img);
			else
				ft_render_img(game, game->img[1], j, i);
		}
	}
	ft_player_move(game, 0, 0, game->player_img);
	return (0);
}

int	ft_init_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	game->map.full = malloc(sizeof(char *) * (game->map.rows + 1));
	if (!game->map.full)
		ft_error_msg("Malloc error\n", game);
	while (i < game->map.rows)
	{
		game->map.full[i] = malloc(sizeof(char) * (game->map.columns + 1));
		game->map_alloc = true;
		if (!game->map.full[i])
			ft_error_msg("Malloc error\n", game);
		j = 0;
		while (j < game->map.columns)
		{
			game->map.full[i][j] = '0';
			j++;
		}
		game->map.full[i][j] = '\0';
		i++;
	}
	game->map.full[i] = NULL;
	return (close(game->fd));
}
