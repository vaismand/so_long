#include "so_long.h"

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


typedef struct    s_data {
    void    *img;
    char    *addr;
    int        bits_per_pixel;
    int        line_length;
    int        endian;
}	t_data;

void    ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int    main(void)
{
    int    i;
    void    *mlx;
    void    *mlx_win;
    t_data    img;

    i = 0;
    //creates the struc for minilibx to work
    mlx = mlx_init();
    //create new window
    mlx_win = mlx_new_window(mlx, 300, 300, "Hello world!");
    //init the new image
    img.img = mlx_new_image(mlx, 300, 300);
    //getting memory address (image address)
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                            &img.endian);
    while(i != 300)
    {
		mlx_hook(mlx_win, 2, 1L<<0, ft_handle_input, &img);
        ft_mlx_pixel_put(&img, i, 10, 0x00FF0000);
        mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
        i++;
    }
    mlx_loop(mlx);

}
