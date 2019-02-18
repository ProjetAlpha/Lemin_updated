/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   put_to_lib.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 12:23:33 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 14:45:00 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_tmp_list	*new_list(void *elem)
{
	t_tmp_list *list;

	list = NULL;
	if (!(list = (t_tmp_list *)malloc(sizeof(t_tmp_list))))
		return (NULL);
	list->len = 0;
	list->elem = elem;
	list->next = NULL;
	return (list);
}

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			i++;
	}
	return (i);
}

t_tmp_list	*add_elem_to_list(void *elem, t_tmp_list *list)
{
	t_tmp_list *curr;

	curr = list;
	if (!list)
	{
		if (!(list = new_list(elem)))
		return (NULL);
	}
	else
	{
		while(curr->next)
			curr = curr->next;
		if (!(curr->next = new_list(elem)))
			return (NULL);
	}
	return (list);
}

t_bool	ft_isnumber(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (FALSE);
		line++;
	}
	return (TRUE);
}
