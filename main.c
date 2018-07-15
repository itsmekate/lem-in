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
		if (tmp[0] == '#' && !sf)
			add_to_file(&all->file, tmp);
		else if ((split = ft_strsplit(tmp, ' ')) && f == 1)
		{
			if (!write_first_room(all, split, sf, tmp))
			{
				free_split(split);
				break ;
			}
			f = 0;
			// free_split(split);
		}
		else if (ft_strchr(tmp, '-') || f == 2)
		{
			if (!(write_links(all, split, tmp, f)))
			{
				free_split(split);
				break ;
			}
			// free_split(split);
			f = 2;
		}
		else if ((split2 = ft_strsplit(tmp, ' ')))
		{
			if(!write_rooms(all, split, sf, tmp))
			{
				free_split(split2);
				break ;
			}
			// free_split(split2);
		}
		else
		{
			if (split)
				free_split(split);
			if (split2)
				free_split(split2);
			break ;
		}
		// if (split)
		// 	free_split(split);
		// if (split2)
		// 		free_split(split2);
		free(tmp);
	}
	if (f != 2)
	{
	/*FREE MAP, FILE, ROOMS*/
		free(all->map);
		free_file(all->file);
		free_rooms(all->rooms);
		ft_putendl("ERROR");
		// system("leaks lem-in");
		exit(0);
	}
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
		/*FREE MAP, FILE, ROOMS*/
		ft_putendl("ERROR");
		// free(all->map);
		// free_file(all->file);
		// free_rooms(all->rooms);

		// system("leaks lem-in");
		exit(0);
	}
	all->map->rooms = ft_count_rooms(all->rooms);
	ft_set_levels(all->map, 2, all->map->start);
	res = ft_find_path(all->map, all->rooms);
	if (res == NULL)
	{
		/*FREE RES*/
		// free_map(all->map);
		// free_file(all->file);
		// free_rooms(all->rooms);
		// free(res);
		ft_putstr("ERROR\n");
		return (0);
	}
	print_lemin(all->file);
	print_out(all->map, res);
	free(all->map);
	free_file(all->file);
	free_rooms(all->rooms);
	free_file(res);
	free(all);
	// system("leaks lem-in");
}
