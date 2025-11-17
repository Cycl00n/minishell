/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 08:32:00 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/17 14:27:47 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_quoted(char *str, int *i, char *result, int *j)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		result[(*j)++] = str[(*i)++];
	if (str[*i] == quote)
		(*i)++;
}

char	*build_unquoted_token(char *str, int *i, int len)
{
	char	*res;
	int		j;

	res = malloc(len + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (str[*i] && j < len)
	{
		if (str[*i] == '\'' || str[*i] == '"')
			copy_quoted(str, i, res, &j);
		else if (ft_is_space(str[*i]) || ft_is_operator(str[*i]))
			break ;
		else
			res[j++] = str[(*i)++];
	}
	res[j] = '\0';
	return (res);
}

static int	quoted_len(char *s, int *p)
{
	int		len;
	char	q;

	len = 0;
	q = s[*p];
	(*p)++;
	while (s[*p] && s[*p] != q)
	{
		len++;
		(*p)++;
	}
	return (len);
}

static int	add_len(char *s, int *p)
{
	int	len;

	len = 0;
	while (s[*p] && !ft_is_space(s[*p]) && !ft_is_operator(s[*p]))
	{
		if (s[*p] == '\'' || s[*p] == '"')
		{
			len += quoted_len(s, p);
			if (!s[*p])
				return (-1);
			(*p)++;
		}
		else
		{
			len++;
			(*p)++;
		}
	}
	return (len);
}

char	*extract_word(char *str, int *i)
{
	int	len;
	int	pos;

	pos = *i;
	len = add_len(str, &pos);
	if (len < 0)
	{
		ft_putstr_fd("Error: unterminated quote\n", 2);
		return (ft_strdup(""));
	}
	return (build_unquoted_token(str, i, len));
}
