#include "lemin.h"

void	add_first_room(t_room **rooms, char **tmp, int s, int f)
{
	*rooms = (t_room*)malloc(sizeof(t_room));
	(*rooms)->name = ft_strdup(holder[0]);
	(*rooms)->num = 0;
	(*rooms)->x = ft_atoi(holder[1]);
	(*rooms)->y = ft_atoi(holder[2]);
	(s) ? (*rooms)->start = 1 : 0;
	(f) ? (*rooms)->finish = 1: 0;
	(*rooms)->next = NULL;
}

// void	add_room(t_room **rooms, char **tmp, int s, int f)
// {
	
// }

void	read_rooms(t_file **file, t_room **rooms, t_l **map)
{
	char	**tmp;
	int		flag;
	int		start;
	int		finish;

	flag = 0;
	map->start = 0;
	map->finish = 0;
	*rooms = (t_room*)malloc(sizeof(t_room));
	while (get_next_line(0, &tmp))
	{
		// if (ft_strcmp(tmp, "##start") == 0)
		// {
		// 	start = 1;
		// 	map->start = 1;
		// }
		// if (ft_strcmp(tmp, "##end") == 0)
		// {
		// 	finish = 1;
		// 	map->finish = 1;
		// }
		// if (map->finish > 1 || map->start > 1)
		// {
		// 	ft_putendl("ERROR");
		// 	ft_putendl("WRONG NUMBER OF CMDS");
		// 	free(*rooms);
		// 	free(rooms);
		// 	free(*file);
		// 	free(file);
		// 	free(*map);
		// 	free(map);
		// 	exit(0);
		// }
		if (!flag)
			add_first_room(&(*rooms), tmp, start, finish);
		// else
		// 	add_room(&(*rooms), tmp, start, finish);
		flag = 1;
		free(tmp);
	}
}

int		main(void)
{
	t_file	*file;
	t_l		*map;
	t_room	*rooms;

	file = NULL;
	map = NULL;
	rooms = NULL;
	read_ants(&file, &map);
	read_rooms(&file, &rooms, &map);
	while (rooms)
	{
		ft_putendl(room->name);
		rooms = rooms->next;
	}
	// while (file)
	// {
		// ft_putnbr(map->ants);
		// file = file->next;
	// }
	// read_links();
}