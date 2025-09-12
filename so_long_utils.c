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

void load_images(t_game *game)
{
	int img_width;
	int img_height;

	game->wall_img = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &img_width, &img_height);
	game->wall_top_img = mlx_xpm_file_to_image(game->mlx, "wall_top.xpm", &img_width, &img_height);
	game->wall_bottom_img = mlx_xpm_file_to_image(game->mlx, "wall_bottom.xpm", &img_width, &img_height);
	game->wall_left_img = mlx_xpm_file_to_image(game->mlx, "wall_left.xpm", &img_width, &img_height);
	game->wall_right_img = mlx_xpm_file_to_image(game->mlx, "wall_right.xpm", &img_width, &img_height);
	game->wall_topleft_img = mlx_xpm_file_to_image(game->mlx, "wall_topleft.xpm", &img_width, &img_height);
	game->wall_topright_img = mlx_xpm_file_to_image(game->mlx, "wall_topright.xpm", &img_width, &img_height);
	game->wall_bottomleft_img = mlx_xpm_file_to_image(game->mlx, "wall_bottomleft.xpm", &img_width, &img_height);
	game->wall_bottomright_img = mlx_xpm_file_to_image(game->mlx, "wall_bottomright.xpm", &img_width, &img_height);

	game->tree_sprites[0] = mlx_xpm_file_to_image(game->mlx, "tree1.xpm", &img_width, &img_height);
	game->tree_sprites[1] = mlx_xpm_file_to_image(game->mlx, "tree2.xpm", &img_width, &img_height);
	game->tree_sprites[2] = mlx_xpm_file_to_image(game->mlx, "tree3.xpm", &img_width, &img_height);
	game->tree_sprites[3] = mlx_xpm_file_to_image(game->mlx, "tree4.xpm", &img_width, &img_height);
	game->tree_sprites[4] = mlx_xpm_file_to_image(game->mlx, "tree5.xpm", &img_width, &img_height);
	game->tree_sprites[5] = mlx_xpm_file_to_image(game->mlx, "tree6.xpm", &img_width, &img_height);

	game->house_img = mlx_xpm_file_to_image(game->mlx, "house.xpm", &img_width, &img_height);
	game->tower_img = mlx_xpm_file_to_image(game->mlx, "tower.xpm", &img_width, &img_height);

	game->enemy_left_sprites[0] = mlx_xpm_file_to_image(game->mlx, "enemy1.xpm", &img_width, &img_height);
	game->enemy_left_sprites[1] = mlx_xpm_file_to_image(game->mlx, "enemy2.xpm", &img_width, &img_height);
	game->enemy_left_sprites[2] = mlx_xpm_file_to_image(game->mlx, "enemy3.xpm", &img_width, &img_height);
	game->enemy_left_sprites[3] = mlx_xpm_file_to_image(game->mlx, "enemy4.xpm", &img_width, &img_height);
	game->enemy_left_sprites[4] = mlx_xpm_file_to_image(game->mlx, "enemy5.xpm", &img_width, &img_height);
	game->enemy_left_sprites[5] = mlx_xpm_file_to_image(game->mlx, "enemy6.xpm", &img_width, &img_height);
	game->enemy_left_sprites[6] = mlx_xpm_file_to_image(game->mlx, "enemy7.xpm", &img_width, &img_height);
	game->enemy_left_sprites[7] = mlx_xpm_file_to_image(game->mlx, "enemy8.xpm", &img_width, &img_height);

	game->enemy_right_sprites[0] = mlx_xpm_file_to_image(game->mlx, "renemy1.xpm", &img_width, &img_height);
	game->enemy_right_sprites[1] = mlx_xpm_file_to_image(game->mlx, "renemy2.xpm", &img_width, &img_height);
	game->enemy_right_sprites[2] = mlx_xpm_file_to_image(game->mlx, "renemy3.xpm", &img_width, &img_height);
	game->enemy_right_sprites[3] = mlx_xpm_file_to_image(game->mlx, "renemy4.xpm", &img_width, &img_height);
	game->enemy_right_sprites[4] = mlx_xpm_file_to_image(game->mlx, "renemy5.xpm", &img_width, &img_height);
	game->enemy_right_sprites[5] = mlx_xpm_file_to_image(game->mlx, "renemy6.xpm", &img_width, &img_height);
	game->enemy_right_sprites[6] = mlx_xpm_file_to_image(game->mlx, "renemy7.xpm", &img_width, &img_height);
	game->enemy_right_sprites[7] = mlx_xpm_file_to_image(game->mlx, "renemy8.xpm", &img_width, &img_height);

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
	game->player_sprites[1] = mlx_xpm_file_to_image(game->mlx, "idle2.xpm",
													&img_width, &img_height);
	game->player_sprites[2] = mlx_xpm_file_to_image(game->mlx, "idle3.xpm",
													&img_width, &img_height);
	game->player_sprites[3] = mlx_xpm_file_to_image(game->mlx, "idle4.xpm",
													&img_width, &img_height);
	game->player_sprites[4] = mlx_xpm_file_to_image(game->mlx, "idle5.xpm",
													&img_width, &img_height);
	game->player_sprites[5] = mlx_xpm_file_to_image(game->mlx, "idle6.xpm",
													&img_width, &img_height);
	game->player_sprites[6] = mlx_xpm_file_to_image(game->mlx, "idle7.xpm",
													&img_width, &img_height);
	game->player_sprites[7] = mlx_xpm_file_to_image(game->mlx, "idle8.xpm",
													&img_width, &img_height);

	game->collectibles_img = mlx_xpm_file_to_image(game->mlx,
												   "collectibles.xpm", &img_width, &img_height);
	game->empty_img = mlx_xpm_file_to_image(game->mlx, "empty.xpm", &img_width,
											&img_height);
	game->exit_img_left = mlx_xpm_file_to_image(game->mlx, "castle.xpm", &img_width, &img_height);
	game->exit_img_right = mlx_xpm_file_to_image(game->mlx, "castle2.xpm", &img_width, &img_height);

}

void init_game(t_game *game, char *file)
{
	game->mlx = mlx_init();
	game->map = NULL;
	allocate_map(game, file);
	fill_map(game, file);
	load_images(game);
	game->win = mlx_new_window(game->mlx, game->width * T, game->height * T,
							   "so_long");
	//Map validations
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
	//Init animations and status
	game->current_frame_right = 0;
	game->current_frame_left = 0;
	game->anim_timer = 0;
	game->anim_speed = 5;
	game->player_dir = DIR_RIGHT;
	game->player_state = IDLE;
	game->tree_frame = 0;
	game->tree_timer = 0;

	// Inizializzazioni nuovo sistema
	game->game_state = PLAYING;
	game->score = 0;
	init_timer(game);
	init_particles(game);
	//Load enemies
	load_enemies(game);

	// Salva filename per restart
	set_map_filename(file);
}

void display_moves(t_game *game)
{
	char *move_count;
	int x;
	int y;
	int color;

	x = 10;
	y = 10;
	move_count = ft_itoa(game->moves);
	color = 0xFF0000;
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

void remove_newline(char *line)
{
	int len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
}

void check_invalid_chars(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->map[i][j] != 'E' && game->map[i][j] != 'P' && game->map[i][j] != 'N' && game->map[i][j] != '1' && game->map[i][j] != '0' && game->map[i][j] != 'C' && game->map[i][j] != 'T' && game->map[i][j] != 'H' && game->map[i][j] != 'A'  && game->map[i][j] != 'F')
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
