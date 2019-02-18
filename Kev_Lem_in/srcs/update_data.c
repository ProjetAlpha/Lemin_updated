/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   update_data.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/16 17:27:07 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 17:32:10 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*update_links(t_room *room)
{
	int		i;
	int		j;
	int		count;
	t_room	**new_links;

	i = -1;
	j = 0;
	count = 0;
	new_links = NULL;
	while (++i < room->link_count)
	{
		if (room->links[i])
			count ++;
	}
	if (!(new_links = new_room_tab(new_links, count)))
		return (NULL);
	i = -1;
	while (++i < room->link_count)
	{
		if (room->links[i])
			new_links[j++] = room->links[i];
	}
	free(room->links);
	room->links = new_links;
	room->link_count = count;
	return (room);
}

static t_data	*update_rooms(t_data *data)
{
	int		i;
	int		j;
	int		count;
	t_room	**new_rooms;

	i = -1;
	j = 0;
	count = 0;
	new_rooms = NULL;
	while (++i < data->room_count)
	{
		if (data->rooms[i])
			count ++;
	}
	if (!(new_rooms = new_room_tab(new_rooms, count)))
		return (NULL);
	i = -1;
	while (++i < data->room_count)
	{
		if (data->rooms[i])
			new_rooms[j++] = data->rooms[i];
	}
	free(data->rooms);
	data->rooms = new_rooms;
	data->room_count = count;
	return (data);
}

t_data			*update_data(t_data *data)
{
	int i;

	i = 0;
	if (!data)
		return (NULL);
	if (data->rooms)
	{
		if (!(data = update_rooms(data)))
				return (NULL);
		while (i < data->room_count)
		{
			if (data->rooms[i]->links)
			{
				if (!(data->rooms[i] = update_links(data->rooms[i])))
					return (NULL);
			}
			i++;
		}
	}
	return (data);
}
