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

void	update_animation(t_game *game)
{
	game->anim_timer++;
	if (game->anim_timer >= 15)
	{
		game->current_frame++;
		if (game->current_frame >= 8)
			game->current_frame = 0;
		game->anim_timer = 0;
	}
}

int	update_game(t_game *game)
{
	 int j = 0;
    while (j < game->num_enemies)
    {
        game->enemies[j].anim_timer++;
        if (game->enemies[j].anim_timer >= 20) // velocità animazione nemici
        {
            game->enemies[j].current_frame++;
            if (game->enemies[j].current_frame >= 8)
                game->enemies[j].current_frame = 0;
            game->enemies[j].anim_timer = 0;
        }
        j++;
    }
	
	update_animation(game);
	render_map(game);
	render_enemies(game);
	return (0);
}
