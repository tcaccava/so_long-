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
                game->enemies[enemy_count].move_timer = 0;
                game->enemies[enemy_count].dir = (rand() % 2 == 0) ? DIR_LEFT : DIR_RIGHT;
                enemy_count++;
                game->map[y][x] = '0';
            }
            x++;
        }
        y++;
    }
}

void check_for_enemy(t_game *game, int new_x, int new_y)
{
    int i;

    i = 0;
    while (i < game->num_enemies)
    {
        if (game->enemies[i].x == new_x && game->enemies[i].y == new_y)
        {
            ft_printf("Game Over! You hit an enemy.\n");
            game->game_state = GAME_OVER;
            return;
        }
        i++;
    }
}

void update_enemy_animation(t_game *game, t_enemy *enemy)
{
    (void)game;
    enemy->anim_timer++;
    if (enemy->anim_timer >= 15) // numero per velocità animazione
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
        void *frame;

        if (game->enemies[j].dir == DIR_LEFT)
            frame = game->enemy_left_sprites[game->enemies[j].current_frame];
        else
            frame = game->enemy_right_sprites[game->enemies[j].current_frame];

        mlx_put_image_to_window(game->mlx, game->win,
                                frame,
                                game->enemies[j].x * T,
                                game->enemies[j].y * T);
        j++;
    }
}

void move_enemies(t_game *game)
{
    int i;
    int new_x;
    int new_y;
    int dir;

    // Non muovere nemici se il gioco non è in corso
    if (game->game_state != PLAYING)
        return;

    i = 0;
    while (i < game->num_enemies)
    {
        game->enemies[i].move_timer++;
        if (game->enemies[i].move_timer >= 90)
        {
            dir = rand() % 4;
            new_x = game->enemies[i].x;
            new_y = game->enemies[i].y;

            if (dir == 0)
                new_y--;
            else if (dir == 1)
                new_y++;
            else if (dir == 2)
            {
                new_x--;
                game->enemies[i].dir = DIR_LEFT;
            }
            else if (dir == 3)
            {
                new_x++;
                game->enemies[i].dir = DIR_RIGHT;
            }

            // controllo collisioni con ostacoli e altri nemici
            if (game->map[new_y][new_x] != '1' && 
                game->map[new_y][new_x] != 'H' && 
                game->map[new_y][new_x] != 'A' && 
                game->map[new_y][new_x] != 'C' && 
                game->map[new_y][new_x] != 'T' && 
                game->map[new_y][new_x] != 'E' && 
                game->map[new_y][new_x] != 'F' &&
                !is_position_occupied_by_enemy(game, new_x, new_y, i))
            {
                // Aggiorna posizione
                game->enemies[i].x = new_x;
                game->enemies[i].y = new_y;
                
                // CONTROLLO COLLISIONE DOPO IL MOVIMENTO DEL NEMICO
                if (check_player_enemy_collision(game))
                {
                    ft_printf("Game Over! A nemico ti ha preso!\n");
                    game->game_state = GAME_OVER;
                    return;
                }
            }
            game->enemies[i].move_timer = 0;
        }
        i++;
    }
}
int is_position_occupied_by_enemy(t_game *game, int x, int y, int current_enemy_index)
{
    int i;

    i = 0;
    while (i < game->num_enemies)
    {
        // Non controllare se stesso
        if (i != current_enemy_index)
        {
            if (game->enemies[i].x == x && game->enemies[i].y == y)
                return (1); // Posizione occupata
        }
        i++;
    }
    return (0); // Posizione libera
}

int check_player_enemy_collision(t_game *game)
{
    int i;

    i = 0;
    while (i < game->num_enemies)
    {
        if (game->enemies[i].x == game->player_x && 
            game->enemies[i].y == game->player_y)
        {
            return (1); // Collisione rilevata
        }
        i++;
    }
    return (0); // Nessuna collisione
}