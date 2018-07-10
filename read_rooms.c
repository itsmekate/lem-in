#include "lemin.h"

void	free_split(char **split)
{
	int k;

	k = 0;
	while (split[k])
	{
		free(split[k]);
		k++;
	}
	free(split);
}

int	add_to_rooms(char **split, char sf, t_room **rooms)
{
	t_room *tmp;

	tmp = (*rooms);
	if (array_size(split) != 3 || !check_max_int(split) 
		|| !check_room(split))
	{
		ft_putendl("ERROR");
		// free_split(split);
		return (0);
	}
	while (tmp->next)
	{
		tmp = tmp->next;
		if (ft_strcmp(tmp->name, split[0]) == 0)
		{
			ft_putendl("ERROR");
			return (0);
		}
		// if ((tmp->start == 1 && sf == 's') 
		// 	|| (tmp->finish == 1 && sf == 'f'))
		// {
		// 	ft_putendl("ERROR");
		// 	return (0);
		// }
	}
	tmp->next = (t_room*)malloc(sizeof(t_room));
	tmp->next->name = ft_strdup(split[0]);
	tmp->next->num = tmp->num + 1;
	tmp->next->x = ft_atoi(split[1]);
	tmp->next->y = ft_atoi(split[2]);
	sf == 's' ? tmp->start = 1 : 0;
	sf == 'f' ? tmp->finish = 1 : 0;
	tmp->next->next = NULL;
	// free_split(split);
	return (1);
}

int	add_first_room(char **split, char sf, t_room **rooms)
{
	if (array_size(split) != 3 || !check_max_int(split) 
		|| !check_room(split))
	{
		ft_putendl("ERROR");
		// free_split(split);
		return (0);
	}
	(*rooms) = (t_room*)malloc(sizeof(t_room));
	(*rooms)->name = ft_strdup(split[0]);
	(*rooms)->num = 0;
	(*rooms)->x = ft_atoi(split[1]);
	(*rooms)->y = ft_atoi(split[2]);
	sf == 's' ? (*rooms)->start = 1 : 0;
	sf == 'f' ? (*rooms)->finish = 1 : 0;
	(*rooms)->next = NULL;
	// free_split(split);
	return (1);
}
