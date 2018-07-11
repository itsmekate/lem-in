/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 14:14:18 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/11 17:29:35 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		count_res(t_file *res)
{
	int count;

	count = 0;
	while (res->next)
	{
		res = res->next;
		count++;
	}
	return (count);
}

void	print_additional(t_l *map, t_file *res2, int count)
{
	while (res2->next)
	{
		if (res2->ant > 0 && (res2->ant <= map->ants))
		{
			ft_putstr("L");
			ft_putnbr(res2->ant);
			ft_putstr("-");
			ft_putstr(res2->str);
			ft_putstr(" ");
		}
		res2 = res2->next;
	}
	(count == 1) ? 0 : ft_putstr("\n");
}

void	print_out(t_l *map, t_file *res)
{
	t_file	*res2;

	res2 = res;
	while (res2->next)
		res2 = res2->next;
	res2->ant = 1;
	while (1)
	{
		res2 = res;
		while (res2)
		{
			if (res2->next == NULL || res2->next->ant != 0)
				res2->ant++;
			if (res2->next == NULL)
			{
				res2 = res;
				print_additional(map, res2, count_res(res));
				break ;
			}
			if (res->ant == map->ants + 1)
				return ;
			res2 = res2->next;
		}
	}
}
