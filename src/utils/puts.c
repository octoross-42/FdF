/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:41:03 by octoross          #+#    #+#             */
/*   Updated: 2024/02/03 18:45:39 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_putstr(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putposnbr(unsigned long n, int uppercase, unsigned long base)
{
	int	len;

	len = 0;
	if (n >= base)
		len += ft_putposnbr(n / base, uppercase, base);
	if ((n % base) < 10)
		ft_putchar('0' + (n % base));
	else
		ft_putchar(('a' + (n % base - 10) + uppercase * ('A' - 'a')));
	len ++;
	return (len);
}

int	ft_putnbr(long long n, int uppercase, unsigned long base, int p)
{
	int				len;
	unsigned long	l;

	if (p && n == 0)
		return (write(1, "(nil)", 5));
	l = n;
	len = 0;
	if (p)
		len += write(1, "0x", 2);
	if (n < 0 && base == 10)
	{
		len += write(1, "-", 1);
		l = -n;
	}
	if (p)
		l = (unsigned long)n;
	else if (base == 16)
		l = (unsigned long)((unsigned int)n);
	return (len + (ft_putposnbr(l, uppercase, base)));
}
