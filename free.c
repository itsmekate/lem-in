/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 21:52:37 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/15 21:52:38 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_file(t_file *file)
{
	while (file)
	{
		free(file->str);
		free(file);
		file = file->next;
	}
	free(file);
}

void	free_map(t_l *map)
{
	int i;

	i = 0;
	while (i < map->rooms)
	{
		free(map->matrix[i]);
		i++;
	}
	free(map->matrix);
	free(map);
}

void	free_rooms(t_room *rooms)
{
	while (rooms)
	{
		free(rooms->name);
		free(rooms);
		rooms = rooms->next;
	}
	free(rooms);
}

void	free_all(t_all *all, t_file *res)
{
	print_lemin(all->file);
	print_out(all->map, res);
	free_map(all->map);
	free_file(all->file);
	free_rooms(all->rooms);
	free_file(res);
	free(all);
}
