/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 18:37:00 by kprasol           #+#    #+#             */
/*   Updated: 2018/05/23 18:37:04 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"
# include "libft/get_next_line.h"

typedef	struct		s_l
{
	int				ants;
	int				rooms;
	int				**matrix;
	int				start;
	int				end;
	int				first;
}					t_l;

typedef	struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				start;
	int				finish;
	int				num;
	struct s_room	*next;
}					t_room;

typedef	struct		s_file
{
	char			*str;
	int				ant;
	struct s_file	*next;
}					t_file;

void			read_ants(t_file **file, t_l **map);
#endif
