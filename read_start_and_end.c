/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_start_and_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 17:30:14 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/11 17:30:15 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	read_start_and_end(t_room **rooms, t_l **map)
{
	t_room *tmp;

	(*map)->start = -1;
	(*map)->end = -1;
	tmp = *rooms;
	while (tmp)
	{
		if (tmp->start == 1)
			(*map)->start = tmp->num;
		if (tmp->finish == 1)
			(*map)->end = tmp->num;
		tmp = tmp->next;
	}
	if ((*map)->start == -1 || (*map)->end == -1)
	{
		// ft_putendl("WRONG NUM OF CMD");
		return (0);
	}
	return (1);
}

int	ft_count_rooms(t_room *room)
{
	int count;

	count = 0;
	while (room)
	{
		count++;
		room = room->next;
	}
	return (count);
}
