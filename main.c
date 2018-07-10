#include "lemin.h"

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
	// ft_putendl("ADDED");
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
		if (tmp[0] == '#')
			add_to_file(file, tmp);
		else if ((split = ft_strsplit(tmp, ' ')) && f == 1)
		{
			add_to_file(file, tmp);
			if (!add_first_room(split, sf, rooms))
				/*FREE MAP, FILE, ROOMS*/
				exit(0);
			f = 0;
			free_split(split);
		}
		else if (ft_strchr(tmp, '-'))
		{
			split = ft_strsplit(tmp, '-');
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
				// ft_putendl("EXIT");
				exit(0);
			}
			free_split(split);
		}
		else if ((split = ft_strsplit(tmp, ' ')))
		{
			add_to_file(file, tmp);
			if(!add_to_rooms(split, sf, rooms)){
				/*FREE MAP, FILE, ROOMS*/
				// ft_putendl("EXIT");
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
}

int		main(void)
{
	t_file	*file;
	// t_file	*head;
	t_l		*map;
	t_room	*rooms;

	file = NULL;
	map = NULL;
	rooms = NULL;
	// head = file;
	read_ants(&file, &map);
	read_rooms_and_links(&file, &map, &rooms);
	// while (rooms)
	// {
	// 	ft_putendl(rooms->name);
	// 	rooms = rooms->next;
	// }
	// while (file)
	// {
	// 	ft_putendl(file->str);
	// 	file = file->next;
	// }
}