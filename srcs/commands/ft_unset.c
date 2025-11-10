/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:00:45 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/06 15:04:55 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_rm_env(char *name, t_env **env)
{
	t_env	*prev;
	t_env 	*curr;

	if (!name || !name[0])
		return ;
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(name, curr->name))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			break;	
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(char **name, t_env **env)
{
	int index;

	if (!name || !name[0])
		return (0);
	index = 0;
	while (name[index])
	{
		if (name[index][0])
			ft_rm_env(name[index], env);
		index++;
	}
}