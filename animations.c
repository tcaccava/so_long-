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
    static int game_over_rendered = 0;
    static int victory_rendered = 0;

    // Se il gioco è in game over o victory, renderizza solo una volta
    if (game->game_state == GAME_OVER)
    {
        if (!game_over_rendered)
        {
            // Aggiorna particelle per l'effetto finale
            update_particles(game);
            
            // Ridisegna la mappa una volta
            render_map(game);
            render_particles(game);
            display_moves(game);
            display_timer(game);
            show_game_over_screen(game);
            
            game_over_rendered = 1;
        }
        return (0);
    }
    else if (game->game_state == VICTORY)
    {
        if (!victory_rendered)
        {
            // Aggiorna particelle per l'effetto finale
            update_particles(game);
            
            // Ridisegna la mappa una volta
            render_map(game);
            render_particles(game);
            display_moves(game);
            display_timer(game);
            show_victory_screen(game);
            
            victory_rendered = 1;
        }
        return (0);
    }
    
    // Reset dei flag quando si torna a giocare
    game_over_rendered = 0;
    victory_rendered = 0;

    // Aggiorna timer se il gioco è in corso
    if (game->game_state == PLAYING)
    {
        update_timer(game);
        
        // animazione alberi
        game->tree_timer++;
        if (game->tree_timer >= 30)
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
    }
    
    // Aggiorna particelle sempre
    update_particles(game);
	
    // ridisegna la mappa
    render_map(game);

    // renderizza nemici nella nuova posizione
    if (game->game_state == PLAYING)
    {
        render_enemies(game);
        render_player(game);
    }
    
    // Renderizza particelle sopra tutto
    render_particles(game);
    
    // Mostra UI
    display_moves(game);
    display_timer(game);

    return (0);
}