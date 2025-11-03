/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:25:06 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/03 14:37:44 by clnicola         ###   ########.fr       */
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
	char				*str;
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

void					free_tabs(char **args);
char					*get_path(char **env);
char					*get_cmd(char **env, char *cmd);
void					handle_cmd_errors(char **args, char *path);
void					exec(char *cmd, char **env);
char					*prompt_name(void);
void					builtin_echo(char *cmd);
void					builtin_exit(char *readl);
int						ft_strisnum(char *str);
void					builtin_env(char *cmd, char **env);
void					parsing(t_data *data);

#endif