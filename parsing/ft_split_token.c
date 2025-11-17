/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:57:17 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/17 14:30:57 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words);
}

void	ft_allocate(char **arr, char const *s, char c)
{
	char		**arr1;
	char const	*str;

	arr1 = arr;
	while (*s)
	{
		while (*s == c)
			++s;
		str = s;
		while (*str && *str != c)
			++str;
		if (str > s)
		{
			*arr1 = ft_substr(s, 0, str - s);
			++arr1;
		}
		s = str;
	}
	*arr1 = NULL;
}

char	**ft_split_token(char const *s, char c)
{
	char	**arr;
	int		size;

	if (!s)
		return (NULL);
	size = ft_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	ft_allocate(arr, s, c);
	return (arr);
}
