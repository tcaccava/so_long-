/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:38:39 by tcaccava          #+#    #+#             */
/*   Updated: 2025/02/05 22:08:32 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	srand(time(NULL));
	if (argc != 2)
	{
		ft_printf("Error\n");
		return (1);
	}
	if (!is_valid_map_extension(argv[1]))
	{
		printf("Error: The map file must have a .ber extension.\n");
		return (1);
	}
	if (is_file_empty(argv[1]))
		return (1);
	init_game(&game, argv[1]);
	render_map(&game);
	ft_printf("=== SO_LONG ENHANCED ===\n");
	ft_printf("Controls: WASD to move, ESC to quit\n");
	ft_printf("During Game Over/Victory: R to restart\n");
	ft_printf("Collect all items and reach the castle to win!\n");
	ft_printf("========================\n");
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, update_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
