/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_paths.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 14:42:08 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 18:31:09 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		number_of_elem(t_tmp_list *list)
{
	int					count;
	t_tmp_list	*tmp;

	count = 0;
	tmp = list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int  eval_path(t_data *data, t_tmp_list *cmp_path)
{
	t_tmp_list	*path;
	t_tmp_list	*curr_path;
	t_tmp_list  *begin;
	t_tmp_list  *begin_2;
	t_room		*room;
	t_room		*room_2;

	path = data->paths;
	curr_path = NULL;
	room = NULL;
	begin = cmp_path;
	while (path)
	{
		curr_path = (t_tmp_list *)path->elem;
			while (curr_path)
			{
				room = (t_room *)curr_path->elem;
				begin_2 = begin;
				while (begin_2)
				{
					room_2 = (t_room *)begin_2->elem;
					if (room == room_2 && !room->is_end && !room->is_start)
						return (1);
					begin_2 = begin_2->next;
				}
				curr_path = curr_path->next;
			}
		path = path->next;
	}
	return (0);
}

int curr_len(t_tmp_list *curr_path)
{
	int i;
	t_tmp_list *begin;

	i = 0;
	begin = curr_path;
	while (begin)
	{
		i++;
		begin = begin->next;
	}
	return (i);
}

int is_duplicate_rooms(t_tmp_list *head_path, t_tmp_list *all_path)
{
	t_tmp_list	*cmp_path;
	t_tmp_list	*curr_path;
	t_tmp_list	*tmp_all;
	t_room			*room_2;
	t_tmp_list  *begin;
	int 				len;
	t_room			*room;

	begin = head_path;
	tmp_all = all_path;
	while (tmp_all)
	{
		curr_path = (t_tmp_list *)tmp_all->elem;
		len = curr_len(curr_path);
		while (curr_path)
		{
			room_2 = (t_room *)curr_path->elem;
			cmp_path = begin;
			while (cmp_path)
			{
				room = (t_room *)cmp_path->elem;
				if (room->name && room_2->name)
				{
					if (room == room_2 && !room->is_end && !room->is_start)
							return (1);
				}
				cmp_path = cmp_path->next;
			}
			curr_path = curr_path->next;
		}
		tmp_all = tmp_all->next;
	}
	return (0);
}

void print_solution(t_tmp_list 	*all_path)
{
	t_tmp_list	*curr_path;
	t_tmp_list	*tmp_all;
	int 				depth;
	int 				c_path;
	t_room			*room;

	tmp_all = all_path;
	c_path = 0;
	while (tmp_all)
	{
		curr_path = (t_tmp_list *)tmp_all->elem;
		depth = 0;
		while (curr_path)
		{
			depth++;
			room = (t_room *)curr_path->elem;
			if (!room->is_end)
				printf("%s=>", room->name);
			else
				printf("%s\n", room->name);
			curr_path = curr_path->next;
		}
		c_path++;
		printf("taille = %d\n", depth);
		tmp_all = tmp_all->next;
	}
}

t_tmp_list	*swap2(t_tmp_list *l1, t_tmp_list *l2)
{
	l1->next = l2->next;
	l2->next = l1;
	return (l2);
}

t_tmp_list	*sort_path(t_tmp_list *head)
{
	t_tmp_list *q;
	t_tmp_list *top;
	t_tmp_list *p;
	int changed;

	top = malloc(sizeof(t_tmp_list));
	changed = 1;
	top->next = head;
	while (changed)
	{
		changed = 0;
		q = top;
		p = top->next;
		while (p->next != NULL)
		{
			if (p->len > p->next->len)
			{
				q->next = swap2(p, p->next);
				changed = 1;
			}
			q = p;
			if (p->next != NULL)
				p = p->next;
		}
	}
	p = top->next;
	return p;
}

t_bool	get_best_path(t_data *data)
{
	t_tmp_list	*path;
	t_tmp_list	*curr_path;
	t_tmp_list	*head_path;
	t_tmp_list 	*all_path;
	t_tmp_list  *head_all;
	t_tmp_list  *begin_path;
	t_tmp_list 	*sorted_path;
	t_room			*room;
	int count;
	int depth;

	path = data->paths;
	begin_path = path;
	curr_path = NULL;
	room = NULL;
	count = 0;
	depth = 0;
	all_path = malloc(sizeof(t_tmp_list));
	all_path->len = 0;
	all_path->elem = NULL;
	all_path->next = NULL;
	head_all = all_path;
	while (path)
	{
		count++;
		curr_path = (t_tmp_list *)path->elem;
		head_path = curr_path;
		depth = 0;
		while (curr_path)
		{
			depth++;
			curr_path = curr_path->next;
		}
		path->len = depth;
		path = path->next;
	}
	sorted_path = sort_path(begin_path);
	count = 0;
	while (sorted_path)
	{
		curr_path = (t_tmp_list *)sorted_path->elem;
		head_path = curr_path;
		if (count == 0)
			add_elem_to_list((void *)head_path, all_path);
		else if (!is_duplicate_rooms(head_path, all_path))
			add_elem_to_list((void *)head_path, all_path);
		count++;
		sorted_path = sorted_path->next;
	}
	print_solution(head_all);
	return (TRUE);
}

t_bool	check_solution(t_data *data)
{
	t_tmp_list	*path;
	t_tmp_list	*curr_path;
	t_room		*room;
	int count;
	int depth;

	path = data->paths;
	curr_path = NULL;
	room = NULL;
	count = 0;
	depth = 0;
	while (path)
	{
		count++;
		curr_path = (t_tmp_list *)path->elem;
		printf("path = ");
		while (curr_path)
		{
			depth++;
			room = (t_room *)curr_path->elem;
			if (!room->is_end)
				printf("%s=>", room->name);
			else
				printf("%s\n", room->name);
			curr_path = curr_path->next;
		}
		printf("taille = %d\n", depth);
		depth = 0;
		printf ("\n");
		path = path->next;
	}
	printf ("nb of path : %d\n", count);
	return (TRUE);
}

void		remove_last(t_tmp_list *list)
{
	t_tmp_list	*last;
	t_tmp_list	*curr;

	curr = list;
	last = NULL;
	while (curr)
	{
		last = curr;
		curr = curr->next;
	}
	free(curr);
	curr = NULL;
	if (last)
		last->next = NULL;
}

t_tmp_list *copy_list(t_tmp_list *list)
{
	t_tmp_list *copy;
	t_tmp_list *curr;

	copy = NULL;
	curr = list;
	while(curr)
	{
		if (!(copy = add_elem_to_list(curr->elem, copy)))
			return (NULL);
		curr = curr->next;
	}
	return (copy);
}

t_room  *best_node(t_room *room)
{
	int i;
	int pos;
	int min;

	i = 0;
	min = INT_MAX;
	pos = 0;
	while (room->links[i])
	{
		if (!room->links[i]->visited && room->links[i]->depth_e < min &&
			!room->links[i]->is_end && !room->links[i]->is_start)
		{
				min = room->links[i]->depth_e;
				pos = i;
		}
		i++;
	}
	if (min == INT_MAX)
		return (NULL);
	return (room->links[pos]);
}

void reset_visited(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->room_count)
	{
		j = 0;
		while (j < data->rooms[i]->link_count)
		{
			if (data->rooms[i]->links[j]->visited == TRUE)
				data->rooms[i]->links[j]->visited = FALSE;
			j++;
		}
		i++;
	}
}

int		find_paths(t_data *data, t_room *curr, t_tmp_list *path)
{
	int i;
	t_tmp_list *tmp_path;
	t_room *choose;

	i = 0;
	tmp_path = NULL;
	tmp_path = copy_list(path);
	tmp_path = add_elem_to_list((void *)curr, tmp_path);
	if (curr->is_end)
	{
		curr->visited = FALSE;
		data->paths = add_elem_to_list((void *)tmp_path, data->paths);
		return (0);
	}
	// plus clean ce serai mieux O_o ! ...
	if (number_of_elem(tmp_path) > 55)
			return (0);
	curr->visited = TRUE;
	choose = best_node(curr);
	if (choose != NULL)
	{
		tmp_path = add_elem_to_list((void *)choose, tmp_path);
		i = 0;
		while (i < choose->link_count)
		{
			if (!choose->links[i]->visited && (choose->depth_s <= choose->links[i]->depth_s || choose->depth_e >= choose->links[i]->depth_e))
					find_paths(data, choose->links[i], tmp_path);
				i++;
		}
	}else
	{
		i = 0;
		while (i < curr->link_count)
		{
			if (!curr->links[i]->visited && (curr->depth_s <= curr->links[i]->depth_s || curr->depth_e >= curr->links[i]->depth_e))
					find_paths(data, curr->links[i], tmp_path);
				i++;
		}
	}
	curr->visited = FALSE;
	free(tmp_path);
	return (0);
}

int		backtrack(t_data *data)
{
	int	i;
	int steps;
	t_room *start;
	char *end;
	char *start_name;
	t_tmp_list	*path;
	t_room *choose;

	i = 0;
	steps = 300;
	path = NULL;
	while (!data->rooms[i]->is_start)
		i++;
	start = data->rooms[i];
	start_name = data->rooms[i]->name;
	i = 0;
	while (!data->rooms[i]->is_end)
		i++;
	end = data->rooms[i]->name;
	i = 0;
	choose = best_node(start);
	while (start->links[i])
	{
			find_paths(data, start->links[i], path);
			reset_visited(data);
		i++;
	}
	get_best_path(data);
	printf("nbre de liens connectes a start: %d\n", i);
	//check_solution(data);
	return (0);
}
