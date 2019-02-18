/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/21 14:35:15 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 15:35:04 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		get_sub_expr_len(const char *sub_expr)
{
	int len;

	len = 0;
	if (*sub_expr == '%')
	{
		sub_expr++;
		len++;
		while (ft_char_belongs_to(FORMAT, *sub_expr) || ft_isdigit(*sub_expr))
		{
			sub_expr++;
			len++;
		}
		if (*sub_expr)
			len++;
	}
	else
		while (*sub_expr && *sub_expr++ != '%')
			len++;
	return (len);
}

static t_bool	fill_curr_format(t_expr *curr, char *sub_expr)
{
	t_format	*curr_format;
	char		*tmp;
	size_t		i;

	tmp = NULL;
	i = 0;
	if (!(curr_format = create_new_t_format()))
		return (FALSE);
	i++;
	if ((tmp = get_flags(sub_expr + i)) != NULL)
	{
		if (!set_flags(curr_format, (char *)tmp))
			return (FALSE);
		i += ft_strlen((const char *)tmp);
	}
	i += set_width(curr_format, get_width(sub_expr + i));
	i += set_point(curr_format, sub_expr + i);
	i += set_precision(curr_format, get_precision(sub_expr + i));
	i += set_length(curr_format, get_length(sub_expr + i));
	curr_format->type = *(sub_expr + i);
	curr->format = curr_format;
	free(sub_expr);
	return (TRUE);
}

t_bool			parse_expression(const char *expr, t_expr **first)
{
	t_expr	*curr;
	int		i;
	int		sub_expr_len;

	i = 0;
	sub_expr_len = 0;
	curr = NULL;
	while (expr[i])
	{
		if ((!*first && (!(*first = create_new_t_expr()))) ||
			(curr && (!(curr->next = create_new_t_expr()))))
			return (FALSE);
		curr = (*first)->next ? curr->next : *first;
		sub_expr_len = get_sub_expr_len(expr + i);
		if (*(expr + i) != '%')
		{
			curr->expr = ft_strsub(expr, i, sub_expr_len);
			curr->length = ft_strlen(curr->expr);
		}
		else if (!fill_curr_format(curr, ft_strsub(expr, i, sub_expr_len)))
			return (FALSE);
		i += sub_expr_len;
	}
	return (TRUE);
}
