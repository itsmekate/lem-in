/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 17:30:28 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/11 17:30:30 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	check_max_int(char **holder)
{
	if ((ft_strlen(holder[1]) > 10 || ft_strlen(holder[2]) > 10) ||
		(ft_strlen(holder[1]) == 10 && (ft_strcmp(holder[1], "2147483647") > 0))
		|| (ft_strlen(holder[2]) == 10
			&& (ft_strcmp(holder[2], "2147483647") > 0)))
	{
		// ft_putendl("WRONG ROOM");
		return (0);
	}
	return (1);
}

int	array_size(char **str)
{
	int	count;

	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

int	ft_check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
			i++;
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int	check_room(char **holder)
{
	if ((holder[0][0] == 'L') || (holder[0][0] == '#'))
	{
		// ft_putstr("INCORRECT ROOM\n");
		return (0);
	}
	if (!ft_check_num(holder[1]) || !ft_check_num(holder[2]))
		return (0);
	return (1);
}
