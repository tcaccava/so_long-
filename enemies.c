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

// Counts enemies
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

// Mallocs and inits enemy's array
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
                game->enemies[enemy_count].dir = (rand() % 2 == 0) ? DIR_LEFT : DIR_RIGHT; // random left-right spawn
                enemy_count++;
                game->map[y][x] = '0'; // updates the spawn position with empty sprites to prevent ghost enemies
            }
            x++;
        }
        y++;
    }
}

// Handles player-enemies collisions
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

// Update enemy's animation timer
void update_enemy_animations(t_game *game)
{
    int j;

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
}

// Render enemy array
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

// Handles enemies movement
void move_enemies(t_game *game)
{
    int i;
    int new_x;
    int new_y;
    int dir;

    if (game->game_state != PLAYING) // doesn't updates enemy position if the game is in victory or gameover state
        return;

    i = 0;
    while (i < game->num_enemies)
    {
        game->enemies[i].move_timer++;
        if (game->enemies[i].move_timer >= 90) // moves enemy every 1.5s
        {
            dir = rand() % 4; // the new direction is random
            new_x = game->enemies[i].x;
            new_y = game->enemies[i].y;
            if (dir == 0) // up
                new_y--;
            else if (dir == 1) // down
                new_y++;
            else if (dir == 2) // left
            {
                new_x--;
                game->enemies[i].dir = DIR_LEFT;
            }
            else if (dir == 3) // right
            {
                new_x++;
                game->enemies[i].dir = DIR_RIGHT;
            }

            // avoids collisions with static elements and prevents enemies overlaps
            if (game->map[new_y][new_x] != '1' &&
                game->map[new_y][new_x] != 'H' &&
                game->map[new_y][new_x] != 'A' &&
                game->map[new_y][new_x] != 'C' &&
                game->map[new_y][new_x] != 'T' &&
                game->map[new_y][new_x] != 'E' &&
                game->map[new_y][new_x] != 'F' &&
                !is_position_occupied_by_enemy(game, new_x, new_y, i)) // prevents enemies overlaps
            {
                // updates positions
                game->enemies[i].x = new_x;
                game->enemies[i].y = new_y;

                if (check_player_enemy_collision(game)) // checks enemy-playes collisions after the movement
                {
                    ft_printf("Game Over! Enemy hit you\n");
                    game->game_state = GAME_OVER;
                    return;
                }
            }
            game->enemies[i].move_timer = 0;
        }
        i++;
    }
}

// Avoids enemies overlap
int is_position_occupied_by_enemy(t_game *game, int x, int y, int current_enemy_index)
{
    int i;

    i = 0;
    while (i < game->num_enemies)
    {
        if (i != current_enemy_index)
        {
            if (game->enemies[i].x == x && game->enemies[i].y == y)
                return (1); // occupied position
        }
        i++;
    }
    return (0); // free position
}

// Checks player-enemy collisions
int check_player_enemy_collision(t_game *game)
{
    int i;

    i = 0;
    while (i < game->num_enemies)
    {
        if (game->enemies[i].x == game->player_x &&
            game->enemies[i].y == game->player_y)
        {
            return (1); // collision
        }
        i++;
    }
    return (0); // no collision
}