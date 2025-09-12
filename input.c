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

// Variabile globale per il filename (necessaria per il restart)
static char *g_map_filename = NULL;

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

		// Gestione input durante game over o victory
	if (game->game_state == GAME_OVER || game->game_state == VICTORY)
	{
		if (key == KEY_R && g_map_filename)
		{
			restart_game(game, g_map_filename);
			return (0);
		}
		return (0); // Ignora altri input durante game over/victory
	}

	// Input normale durante il gioco
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

void set_map_filename(char *filename)
{
	if (g_map_filename)
		free(g_map_filename);
	g_map_filename = ft_strdup(filename);
}

char *get_map_filename(void)
{
	return g_map_filename;
}