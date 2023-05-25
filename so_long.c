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
int	ft_length_line(int fd)
{
	char *line;
    int i;

    i = 0;
	line = get_next_line(fd);
	while (line[i] != '\n')
        i++;
    free(line);
	return (i);
}

int	ft_count_lines(int fd)
{
	char *line;
	int	count;

	count = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break;
		else
		{
			free(line);
			count++;
		}
	}
	return(count);
}
int ft_fill_map(t_game *game, char **argv)
{
    int fd;
    char *line;
    int i;
    int j;

    fd = open(argv[1], O_RDONLY);
    i = 0;
    game->map.full = malloc(sizeof(char *) * game->map.rows); // Move memory allocation outside the loop
	printf("rows: %d\n", game->map.rows);
	printf("columns: %d\n", game->map.columns);
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

void	ft_size_window(t_game *game, char **argv)
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
			if (ft_strlen(line) > game->map.columns)
				game->map.columns = ft_strlen(line) - 1;
			free(line);
			game->map.rows++;
		}
	}
	close(fd);
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

int	ft_draw_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map.rows)
	{
		y = 0;
		while (y < game->map.columns)
		{
			if (game->map.full[x][y] == '1')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->wall.img_ptr, x, y);
			/*else if (game->map.full[x][y] == '0')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor.img_ptr, x, y);
			else if (game->map.full[x][y] == 'C')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->coins.img_ptr, x, y);
			else if (game->map.full[x][y] == 'E')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->open_exit.img_ptr, x, y);
			else if (game->map.full[x][y] == 'P')
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->exit_closed.img_ptr, x, y);*/
			y++;
		}
		x++;
	}
	return (0);
}

int    main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_game	*game;

		game = malloc(sizeof(t_game));
		game->mlx_ptr = mlx_init();
		ft_size_window(game, argv);
		ft_fill_map(game, argv);
		game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.columns * IMG_HEIGHT, game->map.rows * IMG_WIDTH, "so_long");
		ft_init_images(game);
		mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
		mlx_loop_hook(game->mlx_ptr, ft_draw_map, game);
		mlx_loop(game->mlx_ptr);
	}
}
