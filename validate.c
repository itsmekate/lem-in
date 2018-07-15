#include "lemin.h"

int		validate_rooms(char **split, t_room **rooms, char sf)
{
	if (array_size(split) != 3)
	{
		return (0);
	}
	if (!check_sf_and_names(rooms, sf, split))
	{
		return (0);
	}
	return (1);
}

int		validate_links(char **split)
{
	if (ft_strchr(split[0], ' ') || ft_strchr(split[1], ' '))
		return (0);
	if (array_size(split) != 2)
		return (0);
	return (1);
}