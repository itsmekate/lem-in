/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 17:29:28 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/11 17:29:29 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

char	*read_again(char *tmp, t_all *all)
{
	add_to_file(&all->file, tmp);
	free(tmp);
	if (!(get_next_line(0, &tmp)))
	{
		free(all->map);
		free_file(all->file);
		free_rooms(all->rooms);
		free(tmp);
		free(all);
		ft_putendl("ERROR");
		exit(0);
	}
	return (tmp);
}

int		if_first_room(t_all *all, char **split, char sf, char *tmp)
{
	if (!write_first_room(all, split, sf, tmp))
	{
		free_split(split);
		return (0);
	}
	return (1);
}

int		if_room(t_all *all, char **split, char sf, char *tmp)
{
	if (!write_rooms(all, split, sf, tmp))
	{
		free_split(split);
		return (0);
	}
	return (1);
}

void	if_no_links(int f, t_all *all)
{
	if (f != 2)
	{
		free(all->map);
		free_file(all->file);
		free_rooms(all->rooms);
		ft_putendl("ERROR");
		exit(0);
	}
}

void	read_rooms_and_links(t_all *all)
{
	char	*tmp;
	char	sf;
	int		f;
	char	**split;
	char	**split2;

	f = 1;
	split2 = NULL;
	split = NULL;
	while (get_next_line(0, &tmp))
	{
		if ((sf = set_sf(sf, tmp)))
			tmp = read_again(tmp, all);
		split = ft_strsplit(tmp, ' ');
		if (tmp[0] == '#' && !sf)
			add_to_file(&all->file, tmp);
		else if (array_size(split) == 3 && f == 1 && f--)
		{
			if (!if_first_room(all, split, sf, tmp))
				break ;
		}
		else if ((ft_strchr(tmp, '-') && array_size(split) == 1) || f == 2)
		{
			if (!(write_links(all, tmp, f)))
			{
				free_split(split);
				break ;
			}
			f = 2;
		}
		else if (array_size(split) == 3)
		{
			if (!if_room(all, split, sf, tmp))
				break ;
		}
		else
			break ;
		free_split(split);
		free(tmp);
	}
	if_no_links(f, all);
}

int		main(void)
{
	t_all	*all;
	t_file	*res;

	all = NULL;
	set_all(&all);
	read_ants(all);
	read_rooms_and_links(all);
	if (!read_start_and_end(&all->rooms, &all->map))
	{
		ft_putendl("ERROR");
		exit(0);
	}
	all->map->rooms = ft_count_rooms(all->rooms);
	ft_set_levels(all->map, 2, all->map->start);
	res = ft_find_path(all->map, all->rooms);
	if (res == NULL)
	{
		ft_putstr("ERROR\n");
		return (0);
	}
	free_all(all, res);
}
