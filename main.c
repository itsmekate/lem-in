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

void	read_rooms_and_links(t_all *all)
{
	char	*tmp;
	char	sf;
	int		f;
	char	**split;

	f = 1;
	while (get_next_line(0, &tmp))
	{
		if ((sf = set_sf(sf, tmp)))
		{
			add_to_file(&all->file, tmp);
			if (!(get_next_line(0, &tmp)))
			{
				/*FREE MAP, FILE, ROOMS*/
				exit(0);
			}
		}
		if (tmp[0] == '#' && !sf)
			add_to_file(&all->file, tmp);
		else if ((split = ft_strsplit(tmp, ' ')) && f == 1)
		{
			if (!write_first_room(all, split, sf, tmp))
				break ;
			f = 0;
		}
		else if (ft_strchr(tmp, '-'))
		{
			if (!(write_links(all, split, tmp, f)))
			{
				break ;
			}
			f = 2;
		}
		else if ((split = ft_strsplit(tmp, ' ')))
		{
			if(!write_rooms(all, split, sf, tmp))
				break ;
		}
		else
			break ;
		sf = 0;
		free(tmp);
	}
	if (f != 2)
	{
	/*FREE MAP, FILE, ROOMS*/
		ft_putendl("ERROR");
		exit(0);
	}
	add_to_file(&all->file, tmp);
	while(get_next_line(0, &tmp))
	{
		add_to_file(&all->file, tmp);
		free(tmp);
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
		exit(0);
	}
	all->map->rooms = ft_count_rooms(all->rooms);

	ft_set_levels(all->map, 2, all->map->start);
	res = ft_find_path(all->map, all->rooms);
	if (res == NULL)
	{
		/*FREE RES*/
		ft_putstr("ERROR\n");
		return (0);
	}
	print_lemin(all->file);
	print_out(all->map, res);
}
