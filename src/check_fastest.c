/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fastest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaismand <vaismand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:26:57 by vaismand          #+#    #+#             */
/*   Updated: 2023/11/29 15:33:43 by vaismand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static int abs(int n)
// {
//     if (n < 0)
//         return (-n);
//     return (n);
// }

int calculate_total_path_cost(t_game *game)
{
    int total_path_cost = 0;
    int path_cost;
    int collected_chests = 0;

    while (collected_chests < game->map.chests)
    {
        int i = -1;
        while (++i < game->map.rows)
        {
            int j = -1;
            while (++j < game->map.columns)
            {
                if (game->map.full[i][j] == 'C')
                {
                    path_cost = 0;
                    int k = -1;
                    while (++k < game->map.rows)
                    {
                        int l = -1;
                        while (++l < game->map.columns)
                        {
                            if (game->map.full[k][l] == 'P')
                            {
                                path_cost = abs(i - k) + abs(j - l);
                                break;
                            }
                        }
                        if (path_cost != 0)
                            break;
                    }
                    if (total_path_cost < path_cost)
                        total_path_cost = path_cost;
                }
            }
        }
        collected_chests++;
    }
    printf("total_path_cost: %d\n", total_path_cost);
    return (total_path_cost);
}