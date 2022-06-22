/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrozhnova <mrozhnova@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:24:42 by mrozhnova         #+#    #+#             */
/*   Updated: 2022/06/22 11:02:10 by mrozhnova        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static void	malloc_extra_line(t_map *map)
{
	int	**tmp;
	int	i;

	tmp = (int **)malloc(sizeof(int *) * (map->lines));
	ft_memcpy(tmp, map->map, sizeof(int **) * map->lines);
	if (map->lines)
		free(map->map);
	map->map = (int **)malloc(sizeof(int *) * (map->lines + 1));
	i = 0;
	while (i < map->lines)
	{
		map->map[i] = tmp[i];
		i++;
	}
	free(tmp);
}

static int	line_len(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (line[i] != '\n')
		count++;
	return (count);
}

static void	parse_state_line(char *line, t_map *map)
{
	int	i;
	int	col;
	int	len;

	i = 0;
	col = 0;
	len = line_len(line);
	map->map[map->lines] = (int *)malloc(sizeof(int) * len);
	while (line[i])
	{
		map->map[map->lines][col++] = ft_atoi(&line[i]);
		if (map->maxz < map->map[map->lines][col - 1])
			map->maxz = map->map[map->lines][col - 1];
	}
	map->lines++;
	map->cols = col;
}

void	parse_state(char *file, t_map *map)
{
	int		fd;
	char	*line;

	map->name = ft_strdup(file);
	map->lines = 0;
	map->cols = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_msg(3);
	map->maxz = 1;
	while (get_next_line(fd, &line) > 0)
	{
		malloc_extra_line(map);
		parse_state_line(line, map);
		if (!line)
			exit_msg(2);
		free(line);
	}
	if (close(fd) == -1)
		exit_msg(4);
}