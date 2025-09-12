/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 03:13:50 by tcaccava          #+#    #+#             */
/*   Updated: 2025/02/03 03:17:31 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void update_animation(t_game *game)
{
	game->anim_timer++;

	if (game->anim_timer >= 15)
	{
		if (game->player_dir == DIR_RIGHT)
		{
			game->current_frame_right++;
			if (game->current_frame_right >= 8)
				game->current_frame_right = 0;
		}
		else if (game->player_dir == DIR_LEFT)
		{
			game->current_frame_left++;
			if (game->current_frame_left >= 8)
				game->current_frame_left = 0;
		}
		game->anim_timer = 0;
	}
}

void render_player(t_game *game)
{
	void *frame;

	if (game->player_dir == DIR_LEFT)
		frame = game->player_left_sprites[game->current_frame_left];
	else
		frame = game->player_sprites[game->current_frame_right];
	mlx_put_image_to_window(game->mlx, game->win, frame, game->player_x * T, game->player_y * T);
}

int update_game(t_game *game)
{
    int j;

    // animazione alberi
    game->tree_timer++;
    if (game->tree_timer >= 30) // velocità animazione
    {
        game->tree_frame++;
        if (game->tree_frame >= 6)
            game->tree_frame = 0;
        game->tree_timer = 0;
    }

    // animazioni player
    update_animation(game);

    // animazioni nemici
    j = 0;
    while (j < game->num_enemies)
    {
        game->enemies[j].anim_timer++;
        if (game->enemies[j].anim_timer >= 20)
        {
            game->enemies[j].current_frame++;
            if (game->enemies[j].current_frame >= 8)
                game->enemies[j].current_frame = 0;
            game->enemies[j].anim_timer = 0;
        }
        j++;
    }

    // sposta i nemici
    move_enemies(game);
	
    // ridisegna la mappa **dopo aver aggiornato le posizioni dei nemici**
    render_map(game);

    // renderizza nemici nella nuova posizione
    render_enemies(game);

    // renderizza player
    render_player(game);

    return (0);
}
