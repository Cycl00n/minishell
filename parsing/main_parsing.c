/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:08:58 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/04 14:55:47 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_unquoted_token(char *str, int *i, int len)
{
	char	*result;
	char	quote_char;
	int		j;

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	j = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			quote_char = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != quote_char)
				result[j++] = str[(*i)++];
			if (str[*i] == quote_char)
				(*i)++;
		}
		else if (ft_is_space(str[*i]) || ft_is_operator(str[*i]))
			break ;
		else
			result[j++] = str[(*i)++];
	}
	result[j] = '\0';
	return (result);
}

char	*extract_word(char *str, int *i)
{
	int		start;
	int		len;
	char	quote_char;

	start = *i;
	len = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			quote_char = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != quote_char)
			{
				len++;
				(*i)++;
			}
			if (!str[*i])
			{
				ft_putstr_fd("Error: unterminated quote\n", 2);
				return (ft_strdup(""));
			}
			(*i)++;
		}
		else if (ft_is_space(str[*i]) || ft_is_operator(str[*i]))
			break ;
		else
		{
			len++;
			(*i)++;
		}
	}
	*i = start;
	return (build_unquoted_token(str, i, len));
}

char	*extract_operator(char *str, int *i)
{
	char	*operator;
	int		len;

	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' && str[*i
			+ 1] == '>'))
	{
		operator= ft_substr(str, *i, 2);
		len = 2;
	}
	else
	{
		operator= ft_substr(str, *i, 1);
		len = 1;
	}
	*i += len;
	return (operator);
}

t_token	*ft_new_token(char *value, enum token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->token = ft_strdup(value);
	if (!token->token)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*ft_word_to_token(char *input)
{
	int		i;
	t_token	*new;
	t_token	*last;
	t_token	*head;
	char	*str;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_is_space(input[i]))
		{
			i++;
			continue ;
		}
		else if (ft_is_operator(input[i]))
		{
			str = extract_operator(input, &i);
			new = ft_new_token(str, VOID);
			free(str);
		}
		else
		{
			str = extract_word(input, &i);
			new = ft_new_token(str, WORD);
			free(str);
		}
		if (!head)
			head = new;
		else
		{
			last = head;
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
	return (head);
}

void	ft_assign_token_type(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (ft_strcmp(tmp->token, "|") == 0)
			tmp->type = PIPE;
		else if (ft_strcmp(tmp->token, "<<") == 0)
			tmp->type = HEREDOC;
		else if (ft_strcmp(tmp->token, ">>") == 0)
			tmp->type = APPEND;
		else if (ft_strcmp(tmp->token, "<") == 0)
			tmp->type = INPUT;
		else if (ft_strcmp(tmp->token, ">") == 0)
			tmp->type = TRUNC;
		else if (tmp->token[0] == '$' && tmp->token[1] != '\0')
			tmp->type = VAR;
		else
			tmp->type = WORD;
		tmp = tmp->next;
	}
}

void	ft_parsing(t_data *data, char *input)
{
	data->token = ft_word_to_token(input);
	ft_assign_token_type(data);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	t_token	*tmp;

	(void)ac;
	(void)av;
	(void)env;
	data = malloc(sizeof(t_data));
	while (1)
	{
		data->input = readline("testenv$ ");
		if (!data->input)
			break ;
		ft_parsing(data, data->input);
		add_history(data->input);
		tmp = data->token;
		while (tmp)
		{
			printf("[%d] %s\n", tmp->type, tmp->token);
			tmp = tmp->next;
		}
	}
	free(data);
	return (0);
}
