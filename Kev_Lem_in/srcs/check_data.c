/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_data.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 17:34:36 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 14:05:22 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	check_start_and_end(t_data *data)
{
	int i;
	int start_count;
	int end_count;

	i = 0;
	start_count = 0;
	end_count = 0;
	while (data->rooms[i])
	{
		if (data->rooms[i]->is_start && data->rooms[i]->is_end)
			return (FALSE);
		if (data->rooms[i]->is_start)
			start_count++;
		if (data->rooms[i]->is_end)
			end_count++;
		i++;
	}
	if (start_count == 1 && end_count == 1)
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	check_rooms(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data->rooms[i])
	{
		j = i + 1;
		while (data->rooms[j])
		{
			if ((!ft_strcmp(data->rooms[i]->name, data->rooms[j]->name)) ||
				(data->rooms[i]->pos.x == data->rooms[j]->pos.x &&
				data->rooms[i]->pos.y == data->rooms[j]->pos.y))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

t_bool			check_data(t_data *data)
{
	if (!check_start_and_end(data))
		return (clean_exit(data, "Invalid number of start and/or end !"));
	if (!check_rooms(data))
		return (clean_exit(data, "Some rooms have the same name and/or positions !"));
	return (TRUE);
}
