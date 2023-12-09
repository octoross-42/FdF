/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:56:47 by octoross          #+#    #+#             */
/*   Updated: 2023/12/05 21:56:47 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_H

# define UTILS_H

char	**free_until(char **tab, int index);
double	ft_module2(double x, double y);;

# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8192
# endif

typedef struct s_gnl
{
	int				size;
	char			*content;
	int				eof;
	int				eol;
	int				len;
	int				start;
	struct s_gnl	*next;
}		t_gnl;

void	ft_clear_leftovers(t_gnl **leftovers);
void	ft_clean_and_next_lst(t_gnl **line);

char	*gnl(int fd);

char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);

#endif