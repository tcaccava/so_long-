/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 04:04:07 by tcaccava          #+#    #+#             */
/*   Updated: 2025/02/05 23:05:16 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int count_enemies(t_game *game)
{
    int y;
    int x;
    int count;

    count = 0;
    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if (game->map[y][x] == 'N')
                count++;
            x++;
        }
        y++;
    }
    return count;
}


void load_enemies(t_game *game)
{
    int x, y;
    int enemy_count;

    game->num_enemies = count_enemies(game);
    game->enemies = malloc(sizeof(t_enemy) * game->num_enemies);
    if (!game->enemies)
        exit(1);

    enemy_count = 0;
    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            if (game->map[y][x] == 'N')
            {
                game->enemies[enemy_count].x = x;
                game->enemies[enemy_count].y = y;
                game->enemies[enemy_count].current_frame = 0;
                game->enemies[enemy_count].anim_timer = 0;
                enemy_count++;
            }
            x++;
        }
        y++;
    }
}

void	check_for_enemy(t_game *game, int new_x, int new_y)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].x == new_x && game->enemies[i].y == new_y)
		{
			ft_printf("Game Over! You hit an enemy.\n");
			cleanup(game);
			exit(0);
		}
		i++;
	}
}

void update_enemy_animation(t_game *game, t_enemy *enemy)
{
	(void) game;
	enemy->anim_timer++;
    if (enemy->anim_timer >= 15)  // numero per velocità animazione
    {
        enemy->current_frame++;
        if (enemy->current_frame >= 8)
            enemy->current_frame = 0;
        enemy->anim_timer = 0;
    }
}

void render_enemies(t_game *game)
{
    int j = 0;

    while (j < game->num_enemies)
    {
        mlx_put_image_to_window(game->mlx, game->win,
            game->enemy_sprites[game->enemies[j].current_frame],
            game->enemies[j].x * T,
            game->enemies[j].y * T);
        j++;
    }
}
