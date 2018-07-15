/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 17:29:52 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/11 17:29:53 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	*ft_room_name(t_room *room, int id)
{
	while (room)
	{
		if (room->num == id)
			return (room->name);
		room = room->next;
	}
	return (0);
}

int		ft_room_id(t_room *room, char *str)
{
	while (room)
	{
		if (ft_strcmp(room->name, str) == 0)
			return (room->num);
		room = room->next;
	}
	return (0);
}

void	create_matrix(t_l **map)
{
	int j;
	int k;
	t_l *tmp;

	j = 0;
	tmp = *map;
	tmp->matrix = (int**)malloc(sizeof(int*) * (*map)->rooms);
	while (j < (*map)->rooms)
	{
		k = 0;
		tmp->matrix[j] = (int*)malloc(sizeof(int) * (*map)->rooms);
		while (k <= (*map)->rooms)
		{
			tmp->matrix[j][k] = 0;
			k++;
		}
		j++;
	}
}

int		add_to_links(t_l *map, t_room *rooms, char **split)
{
	int		col;
	int		row;

	row = 0;
	if (array_size(split) != 2)
	{
		// free_split(split);
		return (0);
	}
	if (more_room_check(split, *rooms) == 0)
	{
		// free_split(split);
		return (0);
	}
	while (row < map->rooms)
	{
		col = 0;
		while (col < map->rooms)
		{
			if ((col == ft_room_id(rooms, split[1])
				&& row == ft_room_id(rooms, split[0]))
				|| (col == ft_room_id(rooms, split[0])
					&& row == ft_room_id(rooms, split[1])))
				map->matrix[row][col] = 1;
			col++;
		}
		row++;
	}
	// free_split(split);
	return (1);
}
