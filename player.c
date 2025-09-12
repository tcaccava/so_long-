/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:04:30 by tcaccava          #+#    #+#             */
/*   Updated: 2025/02/06 02:31:42 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player_position(t_game *game, char *line, int row)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'P')
		{
			game->player_x = j;
			game->player_y = row;
		}
		j++;
	}
}

void	update_position(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'E')
	{
		if (game->collectibles > 0)
		{
			ft_printf("You must collect all items first!. Remaining:%d\n",
				game->collectibles);
			return ;
		}
		else
		{
			game->game_state = VICTORY;
			ft_printf("Player wins! Total moves: %d\n", game->moves);
			return ;
		}
	}
	game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[game->player_y][game->player_x] = 'P';
}

void	move_player(t_game *game, int new_x, int new_y)
{
	char tile;

	if (game->game_state != PLAYING)
		return;

	tile = game->map[new_y][new_x];

	// Blocchi invalicabili: muro, albero, casa, roccia
	if (tile == '1' || tile == 'A' || tile == 'H' || tile == 'T')
		return;

	// Gestione collectibles
	count_collectibles(game);
	handle_collectible(game, new_x, new_y);

	// Aggiorna posizione
	update_position(game, new_x, new_y);
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	
	 if (check_player_enemy_collision(game))
    {
        ft_printf("Game Over! You were caught by an enemy!\n");
        game->game_state = GAME_OVER;
        return;
    }
	// Quando ha finito di muoversi, torna idle
	game->player_state = IDLE;
}

