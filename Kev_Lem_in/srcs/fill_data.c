/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_data.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 15:04:36 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 13:32:08 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static int	roomcount(t_tmp_list *room_list)
{
	int	count;

	count = 0;
	if (room_list)
	{
		count++;
		while (room_list->next)
		{
			room_list = room_list->next;
			count++;
		}
	}
	return (count);
}

static int	linkcount(t_room *room, t_tmp_list *link_list)
{
	int		count;
	t_link	*link;

	count = 0;
	if (link_list)
	{
		while(link_list)
		{
			link = (t_link *)link_list->elem;
			if (room == link->room_1 || room == link->room_2)
				count++;
			link_list = link_list->next;
		}
	}
	return (count);
}

static void	fill_rooms(t_room **tab, t_tmp_list *room_list)
{
	int			i;
	t_tmp_list	*curr;
	t_tmp_list	*prec;

	i = 0;
	curr = room_list;
	prec = curr;
	while (curr)
	{
		tab[i] = (t_room *)curr->elem;
		curr = curr->next;
		free(prec);
		prec = curr;
		i++;
	}
}

static void	fill_links(t_room *room, t_tmp_list *link_list)
{
	int		i;
	t_link	*link;

	i = 0;
	while (link_list)
	{
		link = (t_link *)link_list->elem;
		if (room == link->room_1)
			room->links[i++] = link->room_2;
		if (room == link->room_2)
			room->links[i++] = link->room_1;
		link_list = link_list->next;
	}
}

t_data		*fill_data(t_tmp *tmp, t_data *data)
{
	int	i;

	data->room_count = roomcount(tmp->room_list);
	i = 0;
	if (!(data->rooms = new_room_tab(data->rooms, data->room_count)))
		return (NULL);
	fill_rooms(data->rooms, tmp->room_list);
	while (data->rooms[i])
	{
		data->rooms[i]->link_count = linkcount(data->rooms[i], tmp->link_list);
		if (!(data->rooms[i]->links = new_room_tab(data->rooms[i]->links,
												data->rooms[i]->link_count)))
			return (NULL);
		fill_links(data->rooms[i], tmp->link_list);
		i++;
	}
	free(tmp);
	return (data);
}
