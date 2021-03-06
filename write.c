/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 21:55:26 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/15 21:55:27 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_room(char *name, t_room *head)
{
	while (head)
	{
		if (ft_strcmp(head->name, name) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

int		write_first_room(t_all *all, char **split, char sf, char *tmp)
{
	if (array_size(split) != 3)
	{
		return (0);
	}
	add_to_file(&all->file, tmp);
	if (!add_first_room(split, sf, &all->rooms))
	{
		exit(0);
	}
	return (1);
}

int		write_links(t_all *all, char *tmp, int f)
{
	char **split;

	if (check_dash(tmp) != 1)
	{
		return (0);
	}
	split = ft_strsplit(tmp, '-');
	if (!validate_links(split))
	{
		free_split(split);
		return (0);
	}
	add_to_file(&all->file, tmp);
	if (f == 0)
	{
		all->map->rooms = ft_count_rooms(all->rooms);
		create_matrix(&all->map);
	}
	if (!(add_to_links(all->map, all->rooms, split)))
	{
		ft_putendl("ERROR");
		exit(0);
	}
	free_split(split);
	return (1);
}

int		write_rooms(t_all *all, char **split, char sf, char *tmp)
{
	if (!validate_rooms(split, &all->rooms, sf))
		return (0);
	add_to_file(&all->file, tmp);
	if (!add_to_rooms(split, sf, &all->rooms))
	{
		ft_putendl("ERROR");
		exit(0);
	}
	return (1);
}
