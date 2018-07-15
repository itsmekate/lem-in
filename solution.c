/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:08:52 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/11 17:30:23 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	push_node_paths(t_file *head, char *str)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = (t_file*)malloc(sizeof(t_file));
	head->next->str = ft_strdup(str);
	head->next->ant = 0;
	head->next->next = NULL;
}

t_file	*first_node_paths(char *str)
{
	t_file	*head;

	head = (t_file*)malloc(sizeof(t_file));
	head->str = ft_strdup(str);
	head->ant = 0;
	head->next = NULL;
	return (head);
}

t_coord	ft_more_find_path(t_coord rc, t_l *map)
{
	while (rc.col < map->rooms)
	{
		if (map->matrix[rc.row][rc.col] <= rc.min
			&& map->matrix[rc.row][rc.col] != 0)
		{
			rc.min = map->matrix[rc.row][rc.col];
			map->matrix[rc.row][rc.col] = 0;
			rc.min_col = rc.col;
		}
		rc.col++;
	}
	return (rc);
}

t_file	*ft_find_path(t_l *map, t_room *head)
{
	t_coord rc;
	t_file	*paths;
	int		i;

	i = 0;
	rc.row = map->end;
	rc.min = map->rooms;
	rc.min_col = map->end;
	paths = NULL;
	while (rc.row != map->start)
	{
		rc.col = 0;
		rc.row = rc.min_col;
		if (paths == NULL)
			paths = first_node_paths(ft_room_name(head, rc.row));
		else
			push_node_paths(paths, ft_room_name(head, rc.row));
		rc = ft_more_find_path(rc, map);
		if (rc.row == rc.min_col)
		{
			return (NULL);
		}
		i++;
	}
	return (paths);
}

void	ft_set_levels(t_l *map, int level, int x)
{
	int	row;
	int	col;

	row = x;
	col = 0;
	while (col < map->rooms)
	{
		if (map->matrix[row][col] > level || map->matrix[row][col] == 1)
		{
			map->matrix[row][col] = level;
			map->matrix[col][row] = level;
			ft_set_levels(map, level + 1, col);
		}
		col++;
	}
}
