#include "lemin.h"

void	print_lemin(t_file *file)
{
	t_file	*go;

	go = file;
	while (go)
	{
		ft_putendl(go->str);
		go = go->next;
	}
	ft_putendl("");
}

void	add_to_file(t_file **file, char *str)
{
	t_file		*tmp;

	tmp = *file;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = (t_file*)malloc(sizeof(t_file));
	tmp->next->str = ft_strdup(str);
	tmp->next->next = NULL;
}

char	set_sf(char sf, char *tmp)
{
	sf = 0;
	(ft_strcmp(tmp, "##start") == 0) ? sf = 's' : 0;
	(ft_strcmp(tmp, "##end") == 0) ? sf = 'f' : 0;
	return (sf);
}

void	set_all(t_all **all)
{
	*all = (t_all*)malloc(sizeof(t_all));
	ft_bzero(*all, sizeof(t_all));
}
