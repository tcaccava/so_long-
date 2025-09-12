/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaccava <tcaccava@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:30:00 by tcaccava          #+#    #+#             */
/*   Updated: 2025/02/06 10:30:00 by tcaccava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_particles(t_game *game)
{
    int i;

    i = 0;
    while (i < MAX_PARTICLES)
    {
        game->particles[i].active = 0;
        game->particles[i].life = 0;
        game->particles[i].max_life = 0;
        game->particles[i].x = 0;
        game->particles[i].y = 0;
        game->particles[i].vel_x = 0;
        game->particles[i].vel_y = 0;
        game->particles[i].color = 0;
        i++;
    }
}

void spawn_particles(t_game *game, int tile_x, int tile_y)
{
    int i;
    int count;
    int center_x;
    int center_y;

    // Centro della tile in pixel
    center_x = tile_x * T + T / 2;
    center_y = tile_y * T + T / 2;

    count = 0;
    i = 0;

    // Spawna 5-8 particelle per collectible
    while (i < MAX_PARTICLES && count < 100)
    {
        if (!game->particles[i].active)
        {
            game->particles[i].active = 1;

            // Posizione iniziale al centro del collectible con piccola variazione
            game->particles[i].x = center_x + (rand() % 16 - 8);
            game->particles[i].y = center_y + (rand() % 16 - 8);

            // Velocità randomica per creare "esplosione"
            game->particles[i].vel_x = (float)(rand() % 12 - 6) * 0.7f;
            game->particles[i].vel_y = (float)(rand() % 12 - 6) * 0.7f;

            // Vita della particella (30-60 frame)
            game->particles[i].max_life = 75 + (rand() % 40);
            game->particles[i].life = game->particles[i].max_life;

            // Colori dorati/gialli per i collectibles
            int color_choice = rand() % 10;
            switch (color_choice)
            {
            case 0:
                game->particles[i].color = 0xFFD700;
                break; // Gold
            case 1:
                game->particles[i].color = 0xFFA500;
                break; // Orange
            case 2:
                game->particles[i].color = 0xFF0000;
                break; // Tomato
            case 3:
                game->particles[i].color = 0xFF1493;
                break; // Deep Pink
            case 4:
                game->particles[i].color = 0x00FFFF;
                break; // Cyan
            case 5:
                game->particles[i].color = 0x00FF00;
                break; // Lime Green
            case 6:
                game->particles[i].color = 0x0000FF;
                break; // Blu
            case 7:
                game->particles[i].color = 0x9370DB;
                break; // Medium Purple
            case 8:
                game->particles[i].color = 0xFFFFFF;
                break; // White
            case 9:
                game->particles[i].color = 0xFFFF00;
                break; // Pure Yellow
            }

            count++;
        }
        i++;
    }
}

void update_particles(t_game *game)
{
    int i;

    i = 0;
    while (i < MAX_PARTICLES)
    {
        if (game->particles[i].active)
        {
            // Aggiorna posizione
            game->particles[i].x += game->particles[i].vel_x;
            game->particles[i].y += game->particles[i].vel_y;

            // Applica gravità leggera
            game->particles[i].vel_y += 0.05f;

            // Frizione dell'aria
            game->particles[i].vel_x *= 0.99f;
            game->particles[i].vel_y *= 0.99f;

            // Riduci vita
            game->particles[i].life--;

            // Disattiva se morta
            if (game->particles[i].life <= 0)
                game->particles[i].active = 0;
        }
        i++;
    }
}

void render_particles(t_game *game)
{
    int i;
    int px, py;
    int size;
    int j, k;

    i = 0;
    while (i < MAX_PARTICLES)
    {
        if (game->particles[i].active)
        {
            px = (int)game->particles[i].x;
            py = (int)game->particles[i].y;

            // Sistema di colori dinamico con fade progressivo
            int current_color = game->particles[i].color;

            // Forma a diamante
            mlx_pixel_put(game->mlx, game->win, px + 1, py, current_color);
            mlx_pixel_put(game->mlx, game->win, px, py + 1, current_color);
            mlx_pixel_put(game->mlx, game->win, px + 2, py + 1, current_color);
            mlx_pixel_put(game->mlx, game->win, px + 1, py + 2, current_color);
            mlx_pixel_put(game->mlx, game->win, px + 1, py + 1, current_color);
        }
        i++;
    }
}