/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 04:09:26 by tcaccava          #+#    #+#             */
/*   Updated: 2025/02/03 05:42:08 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;

	if (key == KEY_ESC)
	{
		ft_printf("HUMAN, HOW DARE YOU CLOSE ME?\n");
		cleanup(game);
		exit(0);
	}

	game->player_state = IDLE; // di default resta fermo

	if (key == KEY_W)
	{
		new_y--;
		game->player_state = WALK;
	}
	else if (key == KEY_A)
	{
		new_x--;
		game->player_dir = DIR_LEFT;
		game->player_state = WALK;
	}
	else if (key == KEY_S)
	{
		new_y++;
		game->player_state = WALK;
	}
	else if (key == KEY_D)
	{
		new_x++;
		game->player_dir = DIR_RIGHT;
		game->player_state = WALK;
	}

	if (game->player_state == WALK)
		move_player(game, new_x, new_y);

	return (0);
}


