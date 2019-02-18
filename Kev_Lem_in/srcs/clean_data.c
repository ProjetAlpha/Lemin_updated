/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clean_data.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/13 13:26:40 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 17:57:13 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	isclean(t_data *data)
{
	int i;

	i = 0;
	while (i < data->room_count)
	{
		if (!data->rooms[i]->is_start && data->rooms[i]->link_count <= 1)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_data	*remove_dead_ends(t_data *data)
{
	int i;

	i = 0;
	while (i < data->room_count)
	{
		if (!data->rooms[i]->is_start && data->rooms[i]->link_count <= 1)
			data->rooms[i] = NULL;
		i++;
	}
	if (!(data = update_data(data)))
		return (NULL);
	return (data);
}

t_data			*clean_data(t_data *data)
{
	while (!isclean(data))
	{
		if (!(data = remove_dead_ends(data)))
			return (NULL);
	}
	return (data);
}
