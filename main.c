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

void	print_lemin(t_file *file)
{
	t_file	*go;

	go = file;
	while (go->next)
	{
		ft_putendl(go->str);
		go = go->next;
	}
	ft_putendl("");
}

void	add_to_file(t_file **file, char *str)
{
	t_file		*tmp;

	tmp = *file;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = (t_file*)malloc(sizeof(t_file));
	tmp->next->str = ft_strdup(str);
	tmp->next->next = NULL;
}

void	read_rooms_and_links(t_file **file, t_l **map,t_room **rooms)
{
	char	*tmp;
	char	sf;
	int		f;
	char	**split;

	f = 1;
	while (get_next_line(0, &tmp))
	{
		(ft_strcmp(tmp, "##start") == 0) ? sf = 's' : 0;
		(ft_strcmp(tmp, "##end") == 0) ? sf = 'f' : 0;
		if (sf)
		{
			add_to_file(file, tmp);
			if (!(get_next_line(0, &tmp)))
			{
				/*FREE MAP, FILE, ROOMS*/
				exit(0);
			}
		}
		if (tmp[0] == '#' && !sf)
			add_to_file(file, tmp);
		else if ((split = ft_strsplit(tmp, ' ')) && f == 1)
		{
			if (array_size(split) != 3)
			{
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT3");
				ft_putendl("ERROR");
				exit(0);
			}
			if (!check_sf_and_names(rooms, sf, split))
			{
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT5");
				exit(0);
			}
			add_to_file(file, tmp);
			if (!add_first_room(split, sf, rooms))
			{
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT6");
				exit(0);
			}
			f = 0;
			free_split(split);
		}
		else if (ft_strchr(tmp, '-'))
		{
			split = ft_strsplit(tmp, '-');
			if (ft_strchr(split[0], ' ') || ft_strchr(split[1], ' '))
			{
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT3");
				ft_putendl("ERROR");
				exit(0);
			}
			if (array_size(split) != 2)
			{
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT3");
				ft_putendl("ERROR");
				exit(0);
			}
			add_to_file(file, tmp);
			if (f == 0)
			{
				(*map)->rooms = ft_count_rooms(*rooms);
				create_matrix(map);
				f = 2;
			}
			else if (!(add_to_links(*map, *rooms, split)))
			{
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT4");
				exit(0);
			}
			free_split(split);
		}
		else if ((split = ft_strsplit(tmp, ' ')))
		{
			if (array_size(split) != 3)
			{
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT3");
				ft_putendl("ERROR");
				exit(0);
			}
			if (!check_sf_and_names(rooms, sf, split))
			{
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT3");
				exit(0);
			}
			add_to_file(file, tmp);
			if(!add_to_rooms(split, sf, rooms)){
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT2");
				exit(0);
			}
			free_split(split);
		}
		else
		{
			ft_putendl("ERROR");
			exit(0);
		}
		sf = 0;
		free(tmp);
	}
	if (f != 2)
	{
	/*FREE MAP, FILE, ROOMS*/
		ft_putendl("ERROR");
		exit(0);
	}
}

int		main(void)
{
	t_file	*file;
	t_l		*map;
	t_room	*rooms;
	t_file	*res;


	file = NULL;
	map = NULL;
	rooms = NULL;
	read_ants(&file, &map);
	read_rooms_and_links(&file, &map, &rooms);
	if (!read_start_and_end(&rooms, &map))
	{
		/*FREE MAP, FILE, ROOMS*/
		exit(0);
	}
	map->rooms = ft_count_rooms(rooms);
	ft_set_levels(map, 2, map->start);
	res = ft_find_path(map, rooms);
	if (res == NULL)
	{
		ft_putstr("ERROR\n");
		return (0);
	}
	print_lemin(file);
	print_out(map, res);
}
