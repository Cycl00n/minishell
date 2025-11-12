/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:49:48 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/12 14:26:12 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//change the current path to the one specified
int	ft_cd(char *path, t_env **env)
{
	int		check;
	char	*cwd;

	if (!path || !path[0])
		return (-1);
	check = chdir(path);
	if (check == -1)
		return (-1);
	ft_set_env("OLDPWD", ft_get_env_value("PWD", env), env);
	cwd = getcwd(NULL, 0);
	ft_set_env("PWD", cwd, env);
	return (0);
}
