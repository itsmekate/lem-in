/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:29:34 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/11 17:29:45 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static	int		only_chars(char *str)
{
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
			return (0);
		str++;
	}
	return (1);
}

static	int		validate_ants(t_l **map, char *tmp)
{
	if (ft_strlen(tmp) > 10)
		return (0);
	else if (ft_strlen(tmp) == 10
		&& ft_strcmp(tmp, "2147483647") > 0)
	{
		return (0);
	}
	if (only_chars(tmp))
		(*map)->ants = ft_atoi(tmp);
	else
		(*map)->ants = 0;
	if ((*map)->ants <= 0)
		return (0);
	return (1);
}

static void		write_ant(t_all *all)
{
	char	*tmp;

	all->file = (t_file*)malloc(sizeof(t_file));
	if (get_next_line(0, &tmp) > 0)
	{
		if (validate_ants(&all->map, tmp) == 0)
		{
			ft_putstr("ERROR\n");
			// ft_putstr("WRONG NUMBER OF ANTS\n");
			// free(*map);
			// free(*file);
			exit(0);
		}
		else
		{
			all->file->str = ft_strdup(tmp);
			free(tmp);
			all->file->next = NULL;
		}
	}
}

void			read_ants(t_all *all)
{
	all->map = (t_l*)malloc(sizeof(t_l));
	write_ant(all);
}
