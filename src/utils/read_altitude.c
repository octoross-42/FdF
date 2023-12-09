/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_altitude.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:22:00 by octoross          #+#    #+#             */
/*   Updated: 2023/12/06 11:22:00 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_read_z(char *word, t_altitude *altitude)
{
	int		sign;
	int		i;
	int		decimal;

	i = 0;
	sign = 1;
	while (word[i] == '-' || word[i] == '+')
	{
		if (word[i] == '-')
			sign = -sign;
		i ++;
	}
	altitude->z = 0;
	while ('0' <= word[i] && word[i] <= '9')
		altitude->z = altitude->z * 10 + (word[i ++] - '0');
	if (word[i] != '.')
		return (altitude->z = sign * altitude->z, i);
	i ++;
	decimal = 10;
	while ('0' <= word[i] && word[i] <= '9')
	{
		altitude->z += (word[i ++] - '0') / decimal;
		decimal *= 10;
	}
	return (altitude->z = sign * altitude->z, i);
}

int	ft_read_color(char *word, t_altitude *altitude)
{
	int		i;
	int		hexa;

	if (word[0] != '0' || !word[0] || word[1] != 'x' || !word[1])
		return (0);
	i = 2;
	while (word[i] && (('0' <= word[i] && word[i] <= '9')
			|| ('A' <= word[i] && word[i] <= 'F')
			|| ('a' <= word[i] && word[i] <= 'f')))
	{
		if ('a' <= word[i] && word[i] <= 'f')
			hexa = word[i] - 'a' + 10;
		else if ('A' <= word[i] && word[i] <= 'F')
			hexa = word[i] - 'A' + 10;
		else
			hexa = word[i] - '0';
		altitude->color = altitude->color * 16 + hexa;
		i ++;
	}
	if (word[i] && word[i] != '\n')
		return (0);
	return (1);
}

t_altitude	ft_read_altitude(char *word)
{
	t_altitude	altitude;
	int			i;

	altitude.isValid = 1;
	altitude.hasColor = 0;
	altitude.color = 0;
	i = ft_read_z(word, &altitude);
	if (word[i] == '\n')
		i ++;
	if (i == 0 || word[i] != ',')
		return (altitude.isValid = !word[i], altitude);
	i ++;
	altitude.hasColor = 1;
	altitude.isValid = ft_read_color(&word[i], &altitude);
	return (altitude);
}
