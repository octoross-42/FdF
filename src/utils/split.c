/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:52:12 by octoross          #+#    #+#             */
/*   Updated: 2023/12/06 13:52:12 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_free_until(void **tab, int index)
{
	int	i;

	i = 0;
	while ((i < index && index >= 0) || tab[i])
		free(tab[i++]);
	free(tab);
}

int	ft_nbr_words(char const *s, char c)
{
	int	nbr_words;
	int	i;

	nbr_words = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i ++;
	while (s[i])
	{
		nbr_words ++;
		while (s[i] && s[i] != c)
			i ++;
		while (s[i] && s[i] == c)
			i ++;
	}
	return (nbr_words);
}

char	*ft_next_word(const char *s, int *i, char c)
{
	char	*word;
	int		len;

	len = 0;
	while (s[*i + len] && s[*i + len] != c)
		len ++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	word[len] = '\0';
	len = 0;
	while (s[*i] && s[*i] != c)
		word[len++] = s[(*i)++];
	while (s[*i] && s[*i] == c)
		(*i)++;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		nbr_words;
	int		i;
	char	**splited;

	if (!s)
		return (0);
	nbr_words = ft_nbr_words(s, c);
	splited = (char **)malloc(sizeof(char *) * (nbr_words + 1));
	if (!splited)
		return (0);
	splited[nbr_words] = 0;
	nbr_words = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i ++;
	while (s[i])
	{
		splited[nbr_words] = ft_next_word(s, &i, c);
		if (!splited[nbr_words])
			return (ft_free_until((void **)splited, nbr_words), NULL);
		nbr_words ++;
	}
	return (splited);
}
