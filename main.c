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
#include <fcntl.h>

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

char	set_sf(char sf, char *tmp)
{
	(ft_strcmp(tmp, "##start") == 0) ? sf = 's' : 0;
	(ft_strcmp(tmp, "##end") == 0) ? sf = 'f' : 0;
	return (sf);
}

void	set_all(t_all **all)
{
	*all = (t_all*)malloc(sizeof(t_all));
	ft_bzero(*all, sizeof(t_all));	
}

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
			validate_rooms(split, &all->rooms, sf);
			add_to_file(&all->file, tmp);
			if (!add_first_room(split, sf, &all->rooms))
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
			validate_links(split/*, file, rooms, map*/);
			add_to_file(&all->file, tmp);
			if (f == 0)
			{
				all->map->rooms = ft_count_rooms(all->rooms);
				create_matrix(&all->map);
				f = 2;
			}
			else if (!(add_to_links(all->map, all->rooms, split)))
			{
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT4");
				exit(0);
			}
			free_split(split);
		}
		else if ((split = ft_strsplit(tmp, ' ')))
		{
			validate_rooms(split, &all->rooms, sf);
			add_to_file(&all->file, tmp);
			if(!add_to_rooms(split, sf, &all->rooms)){
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
	t_all	*all;
	t_file	*res;

	// open("test", O_RDONLY);
	all = NULL;
	set_all(&all);
	read_ants(all);
	read_rooms_and_links(all);
	print_lemin(all->file);
	if (!read_start_and_end(&all->rooms, &all->map))
	{
		/*FREE MAP, FILE, ROOMS*/
		exit(0);
	}
	all->map->rooms = ft_count_rooms(all->rooms);
	ft_set_levels(all->map, 2, all->map->start);
	res = ft_find_path(all->map, all->rooms);
	if (res == NULL)
	{
		/*FREE RES*/
		ft_putstr("ERROR5\n");
		return (0);
	}
	print_lemin(all->file);
	print_out(all->map, res);
}
