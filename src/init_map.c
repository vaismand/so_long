/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:33 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/27 08:49:37 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_fill_map(t_game *game, char **argv)
{
	char	*line;
	int		fd;
	int		i;
	int		j;

	fd = open(argv[1], O_RDONLY);
	i = 0;
	game->map.full = malloc(sizeof(char *) * game->map.rows);
	while (i < game->map.rows)
	{
		j = 0;
		line = get_next_line(fd);
		game->map.full[i] = malloc(sizeof(char) * game->map.columns);
		while (j <= game->map.columns)
		{
			game->map.full[i][j] = line[j];
			j++;
		}
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

void	ft_size_window(t_game *game, char **argv)
{
	int		fd;
	int		line_length;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	game->map.rows = 0;
	game->map.columns = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		else
		{
			line_length = ft_strlen(line) - 1;
			if (line_length > game->map.columns)
				game->map.columns = line_length;
			free(line);
			game->map.rows++;
		}
	}
	close(fd);
}

int	ft_render_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor.img_ptr, j * PXL, i * PXL);
			if (game->map.full[i][j] == '1')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->wall.img_ptr, j * PXL, i * PXL);
			else if (game->map.full[i][j] == 'C')
			{
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->coins.img_ptr, j * PXL, i * PXL);
			}
			else if (game->map.full[i][j] == 'E' && game->map.coins == 0)
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->open_exit.img_ptr, j * PXL, i * PXL);
			else if (game->map.full[i][j] == 'E')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->exit_closed.img_ptr, j * PXL, i * PXL);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player.img_ptr, game->player.x * PXL, game->player.y * PXL);
	return (0);
}
