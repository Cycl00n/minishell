/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:25:06 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/04 17:32:27 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_token
{
	char				*token;
	int					type;
	struct s_token		*previous;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	char				*command;
	char				**args;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char				*input;
	char				**env;
	pid_t				pid;
	int					type;
	t_command			*cmd;
	t_token				*token;
}						t_data;

enum					token_type
{
	WORD,
	VAR,
	PIPE,
	HEREDOC,
	APPEND,
	INPUT,
	TRUNC,
	END,
};

#endif