/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 17:30:02 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/11 17:30:03 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_sf_and_names(t_room **rooms, char sf, char **split)
{
	t_room	*temp;
	int		x;
	int		y;

	temp = *rooms;
	x = ft_atoi(split[1]);
	y = ft_atoi(split[2]);
	while (temp)
	{
		if ((ft_strcmp(temp->name, split[0]) == 0) ||
			(temp->x == x && temp->y == y) ||
			(temp->start == 1 && sf == 's')
			|| (temp->finish == 1 && sf == 'f'))
		{
			// ft_putendl("NAME ALREADY EXCISTS");
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

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

int		add_to_rooms(char **split, char sf, t_room **rooms)
{
	t_room *tmp;

	tmp = (*rooms);
	if (!check_max_int(split) || !check_room(split))
	{
		// free_split(split);
		return (0);
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = (t_room*)malloc(sizeof(t_room));
	tmp->next->start = 0;
	tmp->next->finish = 0;
	tmp->next->name = ft_strdup(split[0]);
	tmp->next->num = tmp->num + 1;
	tmp->next->x = ft_atoi(split[1]);
	tmp->next->y = ft_atoi(split[2]);
	sf == 's' ? tmp->next->start = 1 : 0;
	sf == 'f' ? tmp->next->finish = 1 : 0;
	tmp->next->next = NULL;
	// free_split(split);
	return (1);
}

int		add_first_room(char **split, char sf, t_room **rooms)
{
	if (!check_max_int(split) || !check_room(split))
	{
		// ft_putendl("ERROR3");
		// free_split(split);
		return (0);
	}
	(*rooms) = (t_room*)malloc(sizeof(t_room));
	(*rooms)->start = 0;
	(*rooms)->finish = 0;
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
