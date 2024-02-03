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
void	ft_free_until(void **tab, int index);

size_t	ft_strlen(char *s);
int		ft_strcmp(const char *s1, char *s2);
int		ft_putnbr(long long n, int uppercase, unsigned long base, int p);
int		ft_putstr(char *s);
int		ft_putchar(char c);

char	*gnl(int fd);
int		ft_len_line(char *line);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);
int		ft_max(int a, int b);

#endif