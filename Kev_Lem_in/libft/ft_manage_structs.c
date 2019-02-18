/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_structs.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 13:14:41 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 15:34:53 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_expr		*create_new_t_expr(void)
{
	t_expr *expr_struct;

	if (!(expr_struct = (t_expr *)malloc(sizeof(t_expr))))
		return (NULL);
	expr_struct->expr = NULL;
	expr_struct->length = 0;
	expr_struct->format = NULL;
	expr_struct->next = NULL;
	return (expr_struct);
}

t_format	*create_new_t_format(void)
{
	t_format *format_struct;

	if (!(format_struct = (t_format *)malloc(sizeof(t_format))))
		return (NULL);
	format_struct->flags = NULL;
	format_struct->width = 0;
	format_struct->point = FALSE;
	format_struct->precision = 0;
	format_struct->length = NULL;
	format_struct->type = 0;
	return (format_struct);
}

t_flags		*create_new_t_flags(void)
{
	t_flags *flags_struct;

	if (!(flags_struct = (t_flags *)malloc(sizeof(t_flags))))
		return (NULL);
	flags_struct->hashtag = FALSE;
	flags_struct->minus = FALSE;
	flags_struct->plus = FALSE;
	flags_struct->zero = FALSE;
	flags_struct->space = FALSE;
	flags_struct->coma = FALSE;
	return (flags_struct);
}
