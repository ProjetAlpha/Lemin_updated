/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/20 14:54:38 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 18:30:37 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	print_data(t_data *data)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i < data->room_count)
	{
		printf("Room %s has %d links :\n", data->rooms[i]->name, data->rooms[i]->link_count);
		while(j < data->rooms[i]->link_count)
			printf("%s\n", data->rooms[i]->links[j++]->name);
		j = 0;
		i++;
	}
}

int		main(void)
{
	t_data *data;

	data = NULL;
	if (!(data = new_data(data)))
		return (clean_exit(data, "Data creation error !"));
	if (!(data = parse_data(data)))
		return (clean_exit(data, "Parsing failed !"));
	if (check_data(data))
	{
		if (!(data = clean_data(data)))
			return (clean_exit(data, "Cleaning error !"));
		if (!(data = optimize_data(data)))
			return (clean_exit(data, "Optimizing error !"));
		//print_data(data);
		backtrack(data);
	}
	return (0);
}
