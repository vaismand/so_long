#include "so_long.h"

int	ft_victory(t_game *game)
{
	(void)game;
	printf("You won!");
	return (0);
}
void	ft_render_sprite(t_game *game, t_image sprite, int column, int line)
{
	int	x;
	int	y;

	x = column * 32;
	y = line * 32;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite.img_ptr, x, y);
}

int	ft_close_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
}

void	ft_render_player(t_game *game, int x, int y)
{
	if (game->map.full[y][x] == 'P')
		ft_render_sprite(game, game->player, x, y);
}
void	ft_print_movements(t_game *game)
{
	char	*movements;

	movements = ft_itoa(game->movements);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 10, 0x00FFFFFF, movements);
	free(movements);
}

void	ft_player_move(t_game *game, int x, int y)
{
	if (game->map.full[game->player.y + y][game->player.x + x] != '1')
	{
		if (game->map.full[game->player.y + y][game->player.x + x] == 'C')
		{
			game->map.coins--;
			ft_print_movements(game);
		}
		if (game->map.full[game->player.y + y][game->player.x + x] == 'E')
		{
			if (game->map.coins == 0)
				ft_victory(game);
		}
		game->map.full[game->player.y][game->player.x] = '0';
		game->player.x += x;
		game->player.y += y;
		game->map.full[game->player.y][game->player.x] = 'P';
		game->movements++;
		ft_render_player(game, game->player.x, game->player.y);
	}
}

int	ft_handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_Q || keysym == KEY_ESC)
		ft_close_game(game);
	else if (keysym == KEY_W || keysym == KEY_UP)
		ft_player_move(game, 0, -1);
	else if (keysym == KEY_S || keysym == KEY_DOWN)
		ft_player_move(game, 0, 1);
	else if (keysym == KEY_A || keysym == KEY_LEFT)
		ft_player_move(game, -1, 0);
	else if (keysym == KEY_D || keysym == KEY_RIGHT)
		ft_player_move(game, 1, 0);
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
    while (i < game->map.rows)
    {
        j = 0;
        line = get_next_line(fd);
        game->map.full[i] = malloc(sizeof(char) * game->map.columns); // Allocate memory for each row
        while (j <= game->map.columns)
        {
            game->map.full[i][j] = line[j];
			if (line[j] == 'C')
				game->map.coins++;
            j++;
        }
        free(line);
        i++;
    }
	printf("Coins: %d\n", game->map.coins);
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

void	ft_init_images(t_game *game)
{
	void	*mlx;

	mlx = game->mlx_ptr;
	game->wall = ft_new_image(mlx, WALL_XPM, game);
	game->floor = ft_new_image(mlx, FLOOR_XPM, game);
	game->coins = ft_new_image(mlx, COINS_XPM, game);
	game->open_exit = ft_new_image(mlx, OPEN_EXIT_XPM, game);
	game->exit_closed = ft_new_image(mlx, EXIT_CLOSED_XPM, game);
	game->player = ft_new_image(mlx, PLAYER_XPM, game);
}

t_image	ft_new_image(void *mlx, char *path, t_game *game)
{
	t_image	image;

	image.img_ptr = mlx_xpm_file_to_image(mlx, path, &image.x, &image.y);
	if (image.img_ptr== NULL)
		ft_error_msg("Couldn't find a image. Does it exist?", game);
	return (image);
}

void	ft_init_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			if (game->map.full[i][j] == 'P')
			{
				game->player.x = j;
				game->player.y = i;
				game->map.full[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
	ft_error_msg("Couldn't find the player. Does it exist?", game);
}
void	ft_init_vars(t_game *game)
{
	game->map.rows = 0;
	game->map.columns = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->map.coins = 0;
	game->movements = 0;
}

void	ft_init_game(t_game *game, char **argv)
{
	game->mlx_ptr = mlx_init();
	ft_init_vars(game);
	ft_init_images(game);
	ft_size_window(game, argv);
	ft_fill_map(game, argv);
	ft_init_player(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.columns * IMG_HEIGHT, game->map.rows * IMG_WIDTH, "so_long");
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
            else if (game->map.full[i][j] == 'E')
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->exit_closed.img_ptr, j * IMG_WIDTH, i * IMG_HEIGHT);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player.img_ptr, game->player.x * IMG_WIDTH, game->player.y * IMG_HEIGHT);
    return (0);
}

int    main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_game	*game;
		game = malloc(sizeof(t_game));
		ft_init_game(game, argv);
		mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
		mlx_loop_hook(game->mlx_ptr, ft_render_map, game);
		mlx_loop(game->mlx_ptr);
	}
}
