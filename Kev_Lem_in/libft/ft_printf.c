/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 14:34:19 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 15:35:00 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char		*convert_format(t_format *format, size_t *len, va_list args)
{
	if (format->type == 's')
		return (convert_string(format, len, args));
	if (format->type == 'd' || format->type == 'i')
		return (convert_decimal(format, len, args));
	if (format->type == 'o')
		return (convert_octal(format, len, args));
	if (format->type == 'x')
		return (convert_hexa(format, len, args));
	if (format->type == 'X')
		return (ft_strcapitalize(convert_hexa(format, len, args)));
	if (format->type == 'u')
		return (convert_unsigned(format, len, args));
	if (format->type == 'c')
		return (convert_character(format, len, args));
	if (format->type == 'p')
		return (convert_pointer(format, len, args));
	if (format->type == 'f')
		return (convert_float(format, len, args));
	if (format->type != '\0')
		return (format_character(format, len, format->type));
	return (NULL);
}

static t_bool	convert_expr_list_formats(t_expr **first, va_list args)
{
	t_expr *curr_expr;

	curr_expr = NULL;
	if (!first || !*first)
		return (FALSE);
	curr_expr = *first;
	while (curr_expr)
	{
		if (!curr_expr->expr)
		{
			curr_expr->expr = convert_format(
				curr_expr->format, &curr_expr->length, args);
		}
		if (curr_expr->expr)
			curr_expr->expr = manage_colors(curr_expr);
		curr_expr = curr_expr->next;
	}
	return (TRUE);
}

static void		free_expr_list(t_expr *curr)
{
	if (curr)
	{
		if (curr->format)
		{
			if (curr->format->flags)
				free(curr->format->flags);
			if (curr->format->length)
				free(curr->format->length);
			free(curr->format);
		}
		free(curr->expr);
		if (curr->next)
		{
			free_expr_list(curr->next);
			curr->next = NULL;
		}
		free(curr);
	}
}

int				ft_printf(const char *format, ...)
{
	va_list	args;
	t_expr	*expr_list;
	t_expr	*curr;
	size_t	ret;

	expr_list = NULL;
	curr = NULL;
	ret = 0;
	if (format && *format)
	{
		va_start(args, format);
		if (!parse_expression(format, &expr_list))
			return (-1);
		if (!convert_expr_list_formats(&expr_list, args))
			return (-1);
		curr = expr_list;
		while (curr)
		{
			write(1, curr->expr, curr->length);
			ret += curr->length;
			curr = curr->next;
		}
	}
	free_expr_list(expr_list);
	return (ret);
}
