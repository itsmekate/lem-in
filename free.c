#include "lemin.h"

void	free_file(t_file *file)
{
	while(file)
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
	while (map->matrix[i])
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
