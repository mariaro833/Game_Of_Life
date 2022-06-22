/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozhnova <mrozhnova@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:42:02 by mrozhnova         #+#    #+#             */
/*   Updated: 2022/06/22 21:50:01 by mrozhnova        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/life.h"

static void	generation(t_map *map, double count)
{
	int	i;
	int	j;
	int	life;

	life = 0;
	i = 0;
	while (i < map->lines)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->map_g[i][j] == 1 && (map->map_a[i][j] < 2 || (map->map_a[i][j] > 3)))
			{
				map->map_g[i][j] = 0;
				life = 1;
			}
			else if (map->map_g[i][j] == 0 && map->map_a[i][j] == 3)
			{
				map->map_g[i][j] = 1;
				life = 1;
			}
			j++;
		}
		i++;
	}
	if (life == 0)
	{
		draw_test(map);
		printf("the life has been stabled after the the %1f iteration", count);
		exit(0);
	}
}

void	life(t_map *map, char *str)
{
	double	i;
	double	count;

	count = ft_atoi(str);
	i = 0;
	while (i < count)
	{
		adjasment(map);
		generation(map, i);
		i++;
	}
}
