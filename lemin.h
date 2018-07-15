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

typedef	struct		s_coord
{
	int				row;
	int				col;
	int				min;
	int				min_col;
}					t_coord;

typedef	struct		s_all
{
	t_l				*map;
	t_room			*rooms;
	t_file			*file;
}					t_all;

void				read_ants(t_all *all);
void				add_to_file(t_file **file, char *str);
int					add_to_rooms(char **split, char sf, t_room **rooms);
int					add_first_room(char **split, char sf, t_room **rooms);
int					check_max_int(char **holder);
int					check_room(char **holder);
int					ft_check_num(char *str);
int					array_size(char **str);
void				free_split(char **split);
void				create_matrix(t_l **map);
int					ft_count_rooms(t_room *room);
int					add_to_links(t_l *map, t_room *rooms, char **split);
int					check_sf_and_names(t_room **rooms, char sf, char **split);
int					read_start_and_end(t_room **rooms, t_l **map);
void				ft_set_levels(t_l *map, int level, int x);
t_file				*ft_find_path(t_l *map, t_room *head);
void				print_out(t_l *map, t_file *res);
int					ft_room_id(t_room *room, char *str);
char				*ft_room_name(t_room *room, int id);
int					validate_links(char **split/*t_all *all*/);
int					validate_rooms(char **split, t_room **rooms, char sf);
void				print_lemin(t_file *file);
void				add_to_file(t_file **file, char *str);
char				set_sf(char sf, char *tmp);
void				set_all(t_all **all);
int					write_links(t_all *all, char **split, char *tmp, int f);
int					write_first_room(t_all *all, char **split, char sf, char *tmp);
int					write_rooms(t_all *all, char **split, char sf, char *tmp);
int					more_room_check(char **split, t_room *head);
void				free_file(t_file *file);
void				free_map(t_l *map);
void				free_rooms(t_room *rooms);
#endif
