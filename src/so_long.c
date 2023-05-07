#include "so_long.h"

/*int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (1);
	}
	if (ft_check_extension(argv[1], ".ber") == 0)
	{
		ft_putstr_fd("Error\nWrong file extension\n", 2);
		return (1);
	}
	ft_init_map(&game, argv[1]);

}*/

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	printf("Hello world!\n");
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
}
