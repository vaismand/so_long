/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:33 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/31 19:13:22 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include <time.h>

int	ft_count_rows(char **argv, t_game *game)
{
	char	*line;
	int		fd;
	int		rows;

	fd = open(argv[1], O_RDONLY);
	rows = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		else
		{
			ft_check_empty_line(line, game);
			rows++;
			free(line);
		}
	}
	close(fd);
	return (rows);
}

void	ft_init_map(t_game *game, char **argv)
{
	char	*line;
	int		fd;
	int		i;
	int		j;

	fd = open(argv[1], O_RDONLY);
	i = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		else
		{
			game->map.columns = ft_strlen(line);
			game->map.full[++i] = malloc(sizeof(char) * game->map.columns);
			j = -1;
			while (++j < game->map.columns)
				game->map.full[i][j] = line[j];
			game->map.rows++;
			free(line);
		}
	}
	free(line);
	close(fd);
}

void	ft_put_img(t_game *game, int x, int y, t_image img)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img.img_ptr, x, y);
}

void ft_chest_anim(t_game *game, int x, int y)
{
	static int animationTimer = 0;

	animationTimer++;
	if (animationTimer <= ANIMATION_DELAY)
		ft_put_img(game, x * PXL, y * PXL, game->chest_1);
	else if (animationTimer >= ANIMATION_DELAY * 4)
	{
		ft_put_img(game, x * PXL, y * PXL, game->chest_1);
		animationTimer = 0;
	}
	else if (animationTimer >= ANIMATION_DELAY * 3 && animationTimer < ANIMATION_DELAY * 4)
		ft_put_img(game, x * PXL, y * PXL, game->chest_4);
	else if (animationTimer > ANIMATION_DELAY * 2 && animationTimer < ANIMATION_DELAY * 3)
	  ft_put_img(game, x * PXL, y * PXL, game->chest_3);
	else if (animationTimer > ANIMATION_DELAY)
      ft_put_img(game, x * PXL, y * PXL, game->chest_2);
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
				ft_put_img(game, j * PXL, i * PXL, game->wall);
			else if (game->map.full[i][j] == 'C')
				ft_chest_anim(game, j, i);
			else if (game->map.full[i][j] == 'E' && game->map.coins == 0)
				ft_put_img(game, j * PXL, i * PXL, game->o_exit);
			else if (game->map.full[i][j] == 'E')
				ft_put_img(game, j * PXL, i * PXL, game->c_exit);
			else if (game->map.full[i][j] == 'P')
				ft_put_img(game, j * PXL, i * PXL, game->player_r);
			else if (game->map.full[i][j] == 'X')
				ft_put_img(game, j * PXL, i * PXL, game->enemy);
			else
				ft_put_img(game, j * PXL, i * PXL, game->floor);
		}
	}
	ft_player_move(game, 0, 0, game->player_img);
	return (0);
}

void	ft_check_empty_line(char *map, t_game *game)
{
	if (map[0] == '\0')
		ft_error_msg("Error\nEmpty line in map", game);
}