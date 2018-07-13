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

int		check_dash(char *str)
{
	int count;

	count = 0;
	while(*str)
	{
		if(*str == '-')
			count++;
		str++;
	}
	return (count);
}

int		more_room_check(char **split, t_room head)
{
	if (!is_room(split[0], &head) || !is_room(split[1], &head))
	{
		return (0);
	}
	return (1);
}

int		write_first_room(t_all *all, char **split, char sf, char *tmp)
{
	if (!validate_rooms(split, &all->rooms, sf))
		return (0);
	add_to_file(&all->file, tmp);
	if (!add_first_room(split, sf, &all->rooms))
	{
		/*FREE MAP, FILE, ROOMS*/
		ft_putendl("ERROR");
		// ft_putendl("EXIT6");
		exit(0);
	}
	free_split(split);
	return (1);
}

int		write_links(t_all *all, char **split, char *tmp, int f)
{
	if (check_dash(tmp) != 1)
		return (0);
	split = ft_strsplit(tmp, '-');
	if (!validate_links(split/*, all*/))
		return (0);	
	add_to_file(&all->file, tmp);
	if (f == 0)
	{
		all->map->rooms = ft_count_rooms(all->rooms);
		create_matrix(&all->map);
		// f = 2;
	}
	if (!(add_to_links(all->map, all->rooms, split)))
	{
		/*FREE MAP, FILE, ROOMS*/
		ft_putendl("ERROR");
		// ft_putendl("EXIT4");
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
	if(!add_to_rooms(split, sf, &all->rooms)){
		/*FREE MAP, FILE, ROOMS*/
		ft_putendl("ERROR");
		// ft_putendl("EXIT2");
		exit(0);
	}
	free_split(split);
	return (1);
}