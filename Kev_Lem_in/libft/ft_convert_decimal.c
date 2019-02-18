/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_decimal.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/05 19:37:17 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 15:33:54 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*set_str(t_format *format, size_t len, char c, t_bool is_neg)
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
		if (l > 0 && !format->point && format->flags && !format->flags->minus &&
		(is_neg || (!is_neg && (format->flags->plus || format->flags->space))))
			l--;
	}
	else if (c == ' ')
		l = format->width > len ? format->width - len : 0;
	if (!(str = ft_strnew(l)))
		return (NULL);
	ft_memset((void *)str, c, l);
	return (str);
}

static char	*add_sign(t_format *format, t_bool is_neg)
{
	if (is_neg == TRUE)
		return (ft_strdup("-"));
	else if (format->flags && format->flags->plus)
		return (ft_strdup("+"));
	else if (format->flags && format->flags->space)
		return (ft_strdup(" "));
	return (ft_strnew(0));
}

static char	*format_decimal(t_format *format, size_t *length, long nbr)
{
	char			*str;
	size_t			len;
	t_bool			is_neg;
	unsigned long	u_nbr;

	str = NULL;
	u_nbr = nbr < 0 ? -nbr : nbr;
	is_neg = nbr < 0 ? TRUE : FALSE;
	ft_ulltoa_base(&str, u_nbr, 10);
	len = ft_strlen(str);
	str = ft_strjoin_f(set_str(format, len, '0', is_neg), str);
	if (nbr == 0 && format->point && format->precision == 0)
		str = ft_strdup("");
	str = ft_strjoin_f(add_sign(format, is_neg), str);
	if (format->flags && format->flags->minus)
		str = ft_strjoin_f(str, set_str(format, ft_strlen(str), ' ', is_neg));
	else
		str = ft_strjoin_f(set_str(format, ft_strlen(str), ' ', is_neg), str);
	*length = ft_strlen(str);
	return (str);
}

char		*convert_decimal(t_format *format, size_t *len, va_list args)
{
	if (format->length)
	{
		if (ft_strcmp("hh", format->length) == 0)
		{
			return (format_decimal(format, len, (long)
												(char)va_arg(args, int)));
		}
		if (ft_strcmp("h", format->length) == 0)
		{
			return (format_decimal(format, len, (long)
												(short)va_arg(args, int)));
		}
		if (ft_strcmp("l", format->length) == 0)
			return (format_decimal(format, len, va_arg(args, long)));
		if (ft_strcmp("ll", format->length) == 0)
		{
			return (format_decimal(format, len,
									(long)va_arg(args, long long)));
		}
	}
	return (format_decimal(format, len, (long)va_arg(args, int)));
}
