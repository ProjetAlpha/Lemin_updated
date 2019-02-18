/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 14:21:34 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 14:41:12 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*check_room_name(char *name, t_tmp_list *list)
{
	t_room	*tmp;

	tmp = NULL;
	while (list)
	{
		tmp = (t_room *)list->elem;
		if (!ft_strcmp(name, tmp->name))
			return (list->elem);
		list = list->next;
	}
	return (NULL);
}

int		clean_exit(t_data *data, const char *msg)
{
	(void)data;
	if (msg)
		printf("%s\n", msg);
	exit(0);
	return (0);
}
