/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:25:06 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/10 17:37:31 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*------STRUCT------*/
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
	VOID,
};

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

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
	pid_t				pid;
	int					type;
	t_command			*cmd;
	t_token				*token;
	t_env				**env;
}						t_data;

/*------PARSING------*/
char					**ft_split_token(char const *s, char c);
size_t					ft_words(char const *s, char c);
void					ft_allocate(char **arr, char const *s, char c);
t_token					*ft_new_token(char *value, enum token_type type);
t_token					*ft_word_to_token(char *input);
void					ft_assign_token_type(t_data *data);
void					ft_parsing(t_data *data, char *input);

/*---PARSING_UTILS---*/
void					ft_free_tabs(char **args);
char					*ft_get_path(char **env);
char					*ft_get_cmd(char **env, char *cmd);
void					ft_handle_cmd_errors(char **args, char *path);
char					*ft_prompt_name(void);
int						ft_strisnum(char *str);
int						ft_is_space(char c);
int						ft_is_operator(char c);

/*------COMMANDS------*/


/*---COMMANDS_UTILS---*/
int						ft_set_env(char *name, char *value, t_env **env);
int						ft_rm_env(char *name, t_env **env);
t_env					**ft_initialize_env(void);
#endif
