/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:19:02 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/17 14:31:44 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_operator(char *str, int *i)
{
	char	*operators;
	int		len;

	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' && str[*i
			+ 1] == '>'))
		len = 2;
	else
		len = 1;
	operators = ft_substr(str, *i, len);
	*i += len;
	return (operators);
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

static void	add_back_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static t_token	*make_token(char *input, int *i)
{
	char	*str;
	t_token	*tok;

	if (ft_is_operator(input[*i]))
	{
		str = extract_operator(input, i);
		tok = ft_new_token(str, VOID);
	}
	else
	{
		str = extract_word(input, i);
		tok = ft_new_token(str, WORD);
	}
	free(str);
	return (tok);
}

t_token	*ft_word_to_token(char *input)
{
	t_token	*head;
	t_token	*new;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_is_space(input[i]))
		{
			i++;
			continue ;
		}
		new = make_token(input, &i);
		add_back_token(&head, new);
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
