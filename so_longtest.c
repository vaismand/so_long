#include "so_long.h"

char	*ft_strappend(char **s1, const char *s2)
{
    char	*str;
    int		i;
    int		j;

    if (!s1 || !s2)
        return (NULL);
    str = (char *)malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
    if (!str)
        return (NULL);
    i = -1;
    while ((*s1)[++i])
        str[i] = (*s1)[i];
    j = -1;
    while (s2[++j])
        str[i + j] = s2[j];
    str[i + j] = '\0';
    free(*s1);
    *s1 = NULL;
    return (str);
}

int	ft_close_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
}

int	ft_handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_Q || keysym == KEY_ESC)
		ft_close_game(game);
	return (0);
}

void	ft_error_msg(char *msg, t_game *game)
{
    printf("Error\n%s\n", msg);
    ft_close_game(game);
}

void	ft_init_map(t_game *game, char *argv)
{
	char	*map_temp;
	char	*line_temp;
	int		map_fd;

	map_fd = open(argv, O_RDONLY);
	if (map_fd == -1)
		ft_error_msg("The Map couldn't be opened. Does the Map exist?", game);
	map_temp = ft_strdup("");
	game->map.rows = 0;
	while (true)
	{
		line_temp = get_next_line(map_fd);
		if (line_temp == NULL)
			break ;
		map_temp = ft_strappend(&map_temp, line_temp);
		free(line_temp);
		game->map.rows++;
	}
	close(map_fd);
	game->map.full = ft_split(map_temp, '\n');
	game->map_alloc = true;
	free(map_temp);
}

void	ft_init_images(t_game *game)
{
	void	*mlx;

	mlx = game->mlx_ptr;
	game->wall = ft_new_image(mlx, WALL_XPM, game);
	game->floor = ft_new_image(mlx, FLOOR_XPM, game);
	game->coins = ft_new_image(mlx, COINS_XPM, game);
	game->open_exit = ft_new_image(mlx, OPEN_EXIT_XPM, game);
	game->exit_closed = ft_new_image(mlx, EXIT_CLOSED_XPM, game);
}

t_image	ft_new_image(void *mlx, char *path, t_game *game)
{
	t_image	image;

	image.img_ptr = mlx_xpm_file_to_image(mlx, path, &image.x, &image.y);
	if (image.img_ptr== NULL)
		ft_error_msg("Couldn't find a image. Does it exist?", game);
	return (image);
}

int    main(void)
{
    t_game	*game;

	game = malloc(sizeof(t_game));
    ft_init_map(game, "res/map/map.ber");
    ft_init_images(game);
    mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
    mlx_loop(game->mlx_ptr);
}
