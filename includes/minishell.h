/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:25:06 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/24 10:30:54 by clnicola         ###   ########.fr       */
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

typedef enum s_token_type
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
}						t_token_type;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char				*token;
	t_token_type		type;
	struct s_token		*previous;
	struct s_token		*next;
}						t_token;

typedef struct s_redir
{
	int					type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char				*input;
	pid_t				pid;
	int					type;
	t_command			*cmd;
	t_token				*token;
	t_env				*env;
}						t_data;

/*------PARSING------*/
t_token					*ft_word_to_token(char *input);
void					ft_parsing(t_data *data, char *input);
char					*extract_operator(char *str, int *i);
t_token					*ft_new_token(char *value, t_token_type type);
void					ft_add_back_token(t_token **head, t_token *new);
t_token					*ft_make_token(char *input, int *i);
void					ft_assign_token_type(t_data *data);
char					*extract_word(char *str, int *i);
char					*build_unquoted_token(char *str, int *i, int len);
void					copy_quoted(char *str, int *i, char *result, int *j);
t_command				*parse_tokens(t_token *tok);
t_command				*new_cmd(void);
t_command				*ft_new_command(int arg_count);
void					add_arg(t_command *cmd, char *arg);
void					add_redir(t_command *cmd, int type, char *file);
t_command				*ft_tokens_to_commands(t_token *token_list);
void					ft_add_back_command(t_command **head, t_command *new);
int						ft_count_args(t_token *token_list);
char					**ft_build_args(t_token *token_list, int arg_count);
t_token					*ft_skip_to_next_pipe(t_token *token_list);

/*------UTILS------*/
void					ft_free_tabs(char **args);
char					*ft_get_path(char **env);
char					*ft_get_cmd(char **env, char *cmd);
void					ft_handle_cmd_errors(char **args, char *path);
char					*ft_prompt_name(void);
int						ft_strisnum(char *str);
int						ft_is_space(char c);
int						ft_is_operator(char c);

/*------BUILTIN------*/
void					builtin_echo(char *cmd);
void					builtin_exit(char *cmd);
void					builtin_env(char *cmd, char **env);

/*------HELPER FUNCTIONS------*/
void					ft_init_data(t_data *data, char **env);
void					ft_free_data(t_data *data);
void					ft_signal_handler(int sig);
void					ft_set_signal_handlers(void);
void					ft_unset_signal_handlers(void);
void					ft_exec_cmd(t_command *cmd, char **env);
void					ft_pipex(t_command *cmd, char **env);
void					ft_here_doc(t_command *cmd, char **env);
void					ft_redir_in(t_command *cmd);
void					ft_redir_out(t_command *cmd);
void					ft_exec_builtins(t_command *cmd, char **env);
int						ft_is_builtin(char *cmd);
char					*ft_getenv(char *name, char **env);
void					ft_setenv(char *name, char *value, char **env);
void					ft_unsetenv(char *name, char **env);
void					ft_cd(char *path, char **env);
void					ft_pwd(void);
void					ft_exit(t_data *data);

#endif
