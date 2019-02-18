/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_pointer.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/05 19:40:00 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 15:34:19 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*set_str(t_format *format, size_t len, char c)
{
	char	*str;
	size_t	l;

	str = NULL;
	l = 0;
	if (c == '0')
	{
		if (format->point)
		{
			l = (format->precision > len) ?
				format->precision - len : 0;
		}
		else if (format->flags && format->flags->zero)
			l = (format->width > len) ? format->width - len : 0;
	}
	else if (c == ' ')
		l = format->width > len ? format->width - len : 0;
	if (!(str = ft_strnew(l)))
		return (NULL);
	ft_memset((void *)str, c, l);
	return (str);
}

static char	*set_prefix(char *str, t_format *format)
{
	if (*str == '0' && format->flags && format->flags->zero && !format->point)
	{
		if (*(str + 1) == '0' && *(str + 2))
			str[1] = 'x';
		else if (*(str) == '0' && *(str + 1))
		{
			str[0] = 'x';
			str = ft_strjoin_f(ft_strdup("0"), str);
		}
		else
			str = ft_strjoin_f(ft_strdup("0x"), str);
	}
	else
		str = ft_strjoin_f(ft_strdup("0x"), str);
	return (str);
}

char		*format_pointer(t_format *format, size_t *length,
									unsigned long nbr)
{
	char	*str;
	size_t	len;

	str = NULL;
	ft_ulltoa_base(&str, nbr, 16);
	len = ft_strlen(str);
	str = ft_strjoin_f(set_str(format, len, '0'), str);
	if (nbr == 0 && format->point && format->precision == 0)
	{
		free(str);
		str = ft_strnew(0);
	}
	str = set_prefix(str, format);
	if (format->flags && format->flags->minus)
		str = ft_strjoin_f(str, set_str(format, ft_strlen(str), ' '));
	else
		str = ft_strjoin_f(set_str(format, ft_strlen(str), ' '), str);
	*length = ft_strlen(str);
	return (str);
}

char		*convert_pointer(t_format *format, size_t *len, va_list args)
{
	return (format_pointer(format, len,
			(unsigned long)va_arg(args, void *)));
}
