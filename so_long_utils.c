/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:05:32 by tcaccava          #+#    #+#             */
/*   Updated: 2025/02/06 03:35:38 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->wall_img = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &img_width, &img_height);
	game->wall_top_img = mlx_xpm_file_to_image(game->mlx, "wall_top.xpm", &img_width, &img_height);
	game->wall_bottom_img = mlx_xpm_file_to_image(game->mlx, "wall_bottom.xpm", &img_width, &img_height);
	game->wall_left_img = mlx_xpm_file_to_image(game->mlx, "wall_left.xpm", &img_width, &img_height);
	game->wall_right_img = mlx_xpm_file_to_image(game->mlx, "wall_right.xpm", &img_width, &img_height);
	game->wall_topleft_img = mlx_xpm_file_to_image(game->mlx, "wall_topleft.xpm", &img_width, &img_height);
	game->wall_topright_img = mlx_xpm_file_to_image(game->mlx, "wall_topright.xpm", &img_width, &img_height);
	game->wall_bottomleft_img = mlx_xpm_file_to_image(game->mlx, "wall_bottomleft.xpm", &img_width, &img_height);
	game->wall_bottomright_img = mlx_xpm_file_to_image(game->mlx, "wall_bottomright.xpm", &img_width, &img_height);

	game->enemy_sprites[0] = mlx_xpm_file_to_image(game->mlx, "enemy1.xpm", &img_width, &img_height);
	game->enemy_sprites[1] = mlx_xpm_file_to_image(game->mlx, "enemy2.xpm", &img_width, &img_height);
	game->enemy_sprites[2] = mlx_xpm_file_to_image(game->mlx, "enemy3.xpm", &img_width, &img_height);
	game->enemy_sprites[3] = mlx_xpm_file_to_image(game->mlx, "enemy4.xpm", &img_width, &img_height);
	game->enemy_sprites[4] = mlx_xpm_file_to_image(game->mlx, "enemy5.xpm", &img_width, &img_height);
	game->enemy_sprites[5] = mlx_xpm_file_to_image(game->mlx, "enemy6.xpm", &img_width, &img_height);
	game->enemy_sprites[6] = mlx_xpm_file_to_image(game->mlx, "enemy7.xpm", &img_width, &img_height);
	game->enemy_sprites[7] = mlx_xpm_file_to_image(game->mlx, "enemy8.xpm", &img_width, &img_height);
	
	game->player_left_sprites[0] = mlx_xpm_file_to_image(game->mlx, "lidle1.xpm",
			&img_width, &img_height);
	game->player_left_sprites[1] = mlx_xpm_file_to_image(game->mlx, "lidle2.xpm",
			&img_width, &img_height);
	game->player_left_sprites[2] = mlx_xpm_file_to_image(game->mlx, "lidle3.xpm",
			&img_width, &img_height);
	game->player_left_sprites[3] = mlx_xpm_file_to_image(game->mlx, "lidle4.xpm",
			&img_width, &img_height);
	game->player_left_sprites[4] = mlx_xpm_file_to_image(game->mlx, "lidle5.xpm",
			&img_width, &img_height);
	game->player_left_sprites[5] = mlx_xpm_file_to_image(game->mlx, "lidle6.xpm",
			&img_width, &img_height);
	game->player_left_sprites[6] = mlx_xpm_file_to_image(game->mlx, "lidle7.xpm",
			&img_width, &img_height);
	game->player_left_sprites[7] = mlx_xpm_file_to_image(game->mlx, "lidle8.xpm",
			&img_width, &img_height);
	
	game->player_sprites[0] = mlx_xpm_file_to_image(game->mlx, "idle1.xpm",
			&img_width, &img_height);
	game->player_sprites[1] = mlx_xpm_file_to_image(game->mlx, "idle1.xpm",
			&img_width, &img_height);
	game->player_sprites[2] = mlx_xpm_file_to_image(game->mlx, "idle1.xpm",
			&img_width, &img_height);
	game->player_sprites[3] = mlx_xpm_file_to_image(game->mlx, "idle1.xpm",
			&img_width, &img_height);
	game->player_sprites[4] = mlx_xpm_file_to_image(game->mlx, "idle1.xpm",
			&img_width, &img_height);
	game->player_sprites[5] = mlx_xpm_file_to_image(game->mlx, "idle1.xpm",
			&img_width, &img_height);
	game->player_sprites[6] = mlx_xpm_file_to_image(game->mlx, "idle1.xpm",
			&img_width, &img_height);
	game->player_sprites[7] = mlx_xpm_file_to_image(game->mlx, "idle1.xpm",
			&img_width, &img_height);

	game->collectibles_img = mlx_xpm_file_to_image(game->mlx,
			"collectibles.xpm", &img_width, &img_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "exit.xpm", &img_width,
			&img_height);
	game->empty_img = mlx_xpm_file_to_image(game->mlx, "empty.xpm", &img_width,
			&img_height);
}

void	init_game(t_game *game, char *file)
{
	game->mlx = mlx_init();
	game->map = NULL;
	allocate_map(game, file);
	fill_map(game, file);
	load_images(game);
	game->win = mlx_new_window(game->mlx, game->width * T, game->height * T,
			"so_long");
	check_invalid_chars(game);
	check_map_shape(game);
	check_walls(game);
	check_duplicates(game);
	if (!is_path_valid(game))
	{
		ft_printf("Error: No valid path found in the map.\n");
		cleanup(game);
		exit(1);
	}
	game->current_frame = 0;
	game->anim_timer = 0;
	game->anim_speed = 5;
	game->player_dir = DIR_RIGHT;
	load_enemies(game);
}

void	display_moves(t_game *game)
{
	char	*move_count;
	int		x;
	int		y;
	int		color;

	x = 10;
	y = 10;
	move_count = ft_itoa(game->moves);
	color = 0x000000;
	mlx_string_put(game->mlx, game->win, x, y, color, "Moves: ");
	mlx_string_put(game->mlx, game->win, x + 1, y, color, "Moves: ");
	mlx_string_put(game->mlx, game->win, x, y + 1, color, "Moves: ");
	mlx_string_put(game->mlx, game->win, x + 1, y + 1, color, "Moves: ");
	mlx_string_put(game->mlx, game->win, x + 60, y, color, move_count);
	mlx_string_put(game->mlx, game->win, x + 61, y, color, move_count);
	mlx_string_put(game->mlx, game->win, x + 60, y + 1, color, move_count);
	mlx_string_put(game->mlx, game->win, x + 61, y + 1, color, move_count);
	free(move_count);
}

void	remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
}

void	check_invalid_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->map[i][j] != 'E' && game->map[i][j] != 'P'
				&& game->map[i][j] != 'N' && game->map[i][j] != '1'
				&& game->map[i][j] != '0' && game->map[i][j] != 'C')
			{
				ft_printf("Error: Invalid character '%c' in map.\n",
					game->map[i][j]);
				cleanup(game);
				exit(1);
			}
			j++;
		}
		i++;
	}
}
