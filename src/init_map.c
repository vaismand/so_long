/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:33 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/26 22:13:33 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int ft_fill_map(t_game *game, char **argv)
{
    int fd;
    char *line;
    int i;
    int j;

    fd = open(argv[1], O_RDONLY);
    i = 0;
    game->map.full = malloc(sizeof(char *) * game->map.rows); // Move memory allocation outside the loop
    while (i < game->map.rows)
    {
        j = 0;
        line = get_next_line(fd);
        game->map.full[i] = malloc(sizeof(char) * game->map.columns); // Allocate memory for each row
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

void ft_size_window(t_game *game, char **argv)
{
    int fd;
    char *line;

    fd = open(argv[1], O_RDONLY);
    game->map.rows = 0;
    game->map.columns = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (line == 0)
            break;
        else
        {
            int line_length = ft_strlen(line) - 1;
            if (line_length > game->map.columns)
                game->map.columns = line_length;
            free(line);
            game->map.rows++;
        }
    }
    close(fd);
}

int ft_render_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.rows)
    {
        j = 0;
        while (j < game->map.columns)
        {
            mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor.img_ptr, j * IMG_WIDTH, i * IMG_HEIGHT);
            if (game->map.full[i][j] == '1')
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->wall.img_ptr, j * IMG_WIDTH, i * IMG_HEIGHT);
            else if (game->map.full[i][j] == 'C')
			{
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->coins.img_ptr, j * IMG_WIDTH, i * IMG_HEIGHT);
			}
			else if (game->map.full[i][j] == 'E' && game->map.coins == 0)
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->open_exit.img_ptr, j * IMG_WIDTH, i * IMG_HEIGHT);
            else if (game->map.full[i][j] == 'E')
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->exit_closed.img_ptr, j * IMG_WIDTH, i * IMG_HEIGHT);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player.img_ptr, game->player.x * IMG_WIDTH, game->player.y * IMG_HEIGHT);
    return (0);
}
