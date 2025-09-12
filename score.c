/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_score.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:00:00 by tcaccava          #+#    #+#             */
/*   Updated: 2025/02/06 10:00:00 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void calculate_score(t_game *game)
{
    // Sistema di scoring:
    // Base: 1000 punti
    // Bonus tempo: max 500 punti (diminuisce con il tempo)
    // Bonus mosse: max 300 punti (diminuisce con le mosse eccessive)
    // Malus per ogni secondo oltre i 60: -5 punti
    // Malus per ogni mossa oltre le 50: -2 punti
    
    int base_score = 1000;
    int time_bonus = 0;
    int move_bonus = 0;
    int time_penalty = 0;
    int move_penalty = 0;
    
    // Time bonus (migliore se completato velocemente)
    if (game->game_time_seconds <= 30)
        time_bonus = 500;
    else if (game->game_time_seconds <= 60)
        time_bonus = 250;
    else if (game->game_time_seconds <= 120)
        time_bonus = 100;
    else
        time_penalty = (game->game_time_seconds - 120) * 5;
    
    // Move bonus (migliore se completato con poche mosse)
    if (game->moves <= 20)
        move_bonus = 300;
    else if (game->moves <= 50)
        move_bonus = 150;
    else if (game->moves <= 100)
        move_bonus = 50;
    else
        move_penalty = (game->moves - 100) * 2;
    
    game->score = base_score + time_bonus + move_bonus - time_penalty - move_penalty;
    
    // Score minimo = 0
    if (game->score < 0)
        game->score = 0;
}

void draw_rectangle(t_game *game, int x, int y, int width, int height, int color)
{
    int i, j;
    
    // Disegna un rettangolo semplice pixel per pixel
    // Nota: non è il metodo più efficiente ma funziona con minilibx
    for (i = x; i < x + width && i < game->width * T; i++)
    {
        for (j = y; j < y + height && j < game->height * T; j++)
        {
            // Disegna solo alcuni pixel per creare un effetto semitrasparente
            if ((i + j) % 3 == 0)
                mlx_pixel_put(game->mlx, game->win, i, j, color);
        }
    }
}

void draw_text_centered(t_game *game, char *text, int y, int color)
{
    int window_width = game->width * T;
    int text_width = ft_strlen(text) * 6; // Approssimazione larghezza carattere
    int x = (window_width - text_width) / 2;
    
    // Ombra per leggibilità
    mlx_string_put(game->mlx, game->win, x + 1, y + 1, 0x000000, text);
    mlx_string_put(game->mlx, game->win, x, y, color, text);
}

void show_game_over_screen(t_game *game)
{
    char moves_text[50];
    char time_text[50];
    char score_text[50];
    int center_y = (game->height * T) / 2;
    int minutes, seconds;
    
    calculate_score(game);
    
    // Sfondo semi-trasparente
    draw_rectangle(game, 50, center_y - 100, game->width * T - 100, 200, 0x000000);
    
    // Titolo
    draw_text_centered(game, "GAME OVER!", center_y - 80, 0xFF0000);
    
    // Statistiche
    minutes = game->game_time_seconds / 60;
    seconds = game->game_time_seconds % 60;
    
    // Prepara stringhe
    ft_printf(""); // Reset printf se necessario
    sprintf(moves_text, "Moves: %d", game->moves);
    sprintf(time_text, "Time: %02d:%02d", minutes, seconds);
    sprintf(score_text, "Score: %d", game->score);
    
    // Mostra statistiche
    draw_text_centered(game, moves_text, center_y - 40, 0xFFFFFF);
    draw_text_centered(game, time_text, center_y - 20, 0xFFFFFF);
    draw_text_centered(game, score_text, center_y, 0xFFFF00);
    
    // Istruzioni
    draw_text_centered(game, "Press R to restart", center_y + 40, 0x00FF00);
    draw_text_centered(game, "Press ESC to quit", center_y + 60, 0x00FF00);
}

void show_victory_screen(t_game *game)
{
    char moves_text[50];
    char time_text[50];
    char score_text[50];
    int center_y = (game->height * T) / 2;
    int minutes, seconds;
    
    calculate_score(game);
    
    // Sfondo semi-trasparente dorato
    draw_rectangle(game, 50, center_y - 100, game->width * T - 100, 200, 0x332200);
    
    // Titolo
    draw_text_centered(game, "VICTORY!", center_y - 80, 0x00FF00);
    draw_text_centered(game, "You escaped the dungeon!", center_y - 60, 0xFFFF00);
    
    // Statistiche
    minutes = game->game_time_seconds / 60;
    seconds = game->game_time_seconds % 60;
    
    sprintf(moves_text, "Moves: %d", game->moves);
    sprintf(time_text, "Time: %02d:%02d", minutes, seconds);
    sprintf(score_text, "Final Score: %d", game->score);
    
    // Mostra statistiche
    draw_text_centered(game, moves_text, center_y - 20, 0xFFFFFF);
    draw_text_centered(game, time_text, center_y, 0xFFFFFF);
    draw_text_centered(game, score_text, center_y + 20, 0xFFFF00);
    
    // Valutazione performance
    if (game->score >= 1500)
        draw_text_centered(game, "PERFECT RUN!", center_y + 40, 0x00FFFF);
    else if (game->score >= 1000)
        draw_text_centered(game, "Great job!", center_y + 40, 0x00FFFF);
    else if (game->score >= 500)
        draw_text_centered(game, "Not bad!", center_y + 40, 0x00FFFF);
    else
        draw_text_centered(game, "Try to be faster!", center_y + 40, 0x00FFFF);
    
    // Istruzioni
    draw_text_centered(game, "Press R to play again", center_y + 70, 0x00FF00);
    draw_text_centered(game, "Press ESC to quit", center_y + 90, 0x00FF00);
}

void restart_game(t_game *game, char *filename)
{
    // Nota: questa funzione richiederà una variabile globale per il filename
    // o modifiche alla struttura per salvare il percorso del file
    
    // Reset dei valori di gioco
    game->game_state = PLAYING;
    game->moves = 0;
    game->score = 0;
    game->current_frame_right = 0;
    game->current_frame_left = 0;
    game->anim_timer = 0;
    game->player_dir = DIR_RIGHT;
    game->player_state = IDLE;
    game->tree_frame = 0;
    game->tree_timer = 0;
    
    // Reset timer
    init_timer(game);
    
    // Reset particelle
    init_particles(game);
    
    // Libera e ricarica la mappa
    int i = 0;
    while (i < game->height && game->map[i])
    {
        free(game->map[i]);
        i++;
    }
    free(game->map);
    free(game->enemies);
    
    // Ricarica tutto
    allocate_map(game, filename);
    fill_map(game, filename);
    load_enemies(game);
    
    // Renderizza la nuova mappa
    render_map(game);
}