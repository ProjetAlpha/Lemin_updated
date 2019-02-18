/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   optimize_data.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/15 14:45:38 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 18:17:53 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		depth_from_start(t_room *room, int depth)
{
	int i;

	i = 0;
	room->visited = TRUE;
	room->depth_s = depth;
	if (room->is_end)
	{
		room->visited = FALSE;
		return(0);
	}
	while (i < room->link_count)
	{
		if (!room->links[i]->visited && (room->links[i]->depth_s == 0 ||
			room->links[i]->depth_s > depth + 1))
			depth_from_start(room->links[i], depth + 1);
		i++;
	}
	room->visited = FALSE;
	return(0);
}

int		depth_from_end(t_room *room, int depth)
{
	int i;

	i = 0;
	room->visited = TRUE;
	room->depth_e = depth;
	depth ++;
	if (room->is_start)
	{
		room->visited = FALSE;
		return(0);
	}
	while (i < room->link_count)
	{
		if (!room->links[i]->visited && (room->links[i]->depth_e == 0 ||
			room->links[i]->depth_e > depth))
			depth_from_end(room->links[i], depth);
		i++;
	}
	room->visited = FALSE;
	return(0);
}

t_data	*remove_unreachables(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < data->room_count)
	{
		while (j < data->rooms[i]->link_count)
		{
			if ((!data->rooms[i]->links[j]->is_end && !data->rooms[i]->links[j]->depth_e) ||
				(!data->rooms[i]->links[j]->is_start && !data->rooms[i]->links[j]->depth_s))
				data->rooms[i]->links[j] = NULL;
			j++;
		}
		if ((!data->rooms[i]->is_end && data->rooms[i]->depth_e == 0) ||
			(!data->rooms[i]->is_start && data->rooms[i]->depth_s == 0))
			data->rooms[i] = NULL;
		i++;
		j = 0;
	}
	if (!(data = update_data(data)))
		return (NULL);
	return (data);
}

t_data	*optimize_end(t_data *data)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < data->room_count && !data->rooms[i]->is_end)
		i++;
	while (j < data->rooms[i]->link_count)
	{
		while (k < data->rooms[i]->links[j]->link_count)
		{
			if (!data->rooms[i]->links[j]->links[k]->is_end)
				data->rooms[i]->links[j]->links[k] = NULL;
			k++;
		}
		j++;
		k = 0;
	}
	if (!(data = update_data(data)))
		return (NULL);
	return (data);
}

t_data	*optimize_data(t_data *data)
{
	int i;

	i = 0;
	while (!data->rooms[i]->is_start)
		i++;
	depth_from_start(data->rooms[i], 0);
	i = 0;
	while (!data->rooms[i]->is_end)
		i++;
	depth_from_end(data->rooms[i], 0);
	if (!(data = remove_unreachables(data)))
		return (NULL);
	if (!(data = optimize_end(data)))
		return (NULL);
	return (data);
}
