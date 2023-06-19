/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 00:37:19 by isalama           #+#    #+#             */
/*   Updated: 2023/06/19 01:41:54 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	export_new(t_env **env, int index, char *identifier);

bool	is_exportable(char *identifier){
	int index;

	index = false;
	if	(!(is_alpha(identifier[index]) || identifier[index] == '_'))
		return false;
	index++;
	while(identifier[index] && identifier[index] != '+' && identifier[index] != '=')
	{
		if(!(is_alpha(identifier[index]) || is_digit(identifier[index]) || identifier[index] == '_'))
			return false;
		index++;
	}
	if(identifier[index] == '+' && (!identifier[index + 1] || (identifier[index + 1] && identifier[index + 1] != '='))) 
		return false;
	if(identifier[index] && identifier[index] != '=' && identifier[index] != '+')
		return false;
	return true;
}

void	export_append(t_env **env, int plus_pos, char *identifier){
	char *key = ft_substr(identifier, 0, plus_pos);
	char *new_value;
	t_env *envirement = *env;

	while(envirement){
		if(ft_strcmp(envirement->key, key) == 0){
			new_value = ft_strjoin(envirement->value, identifier + plus_pos + 2, 0);
			free(envirement->value);
			envirement->value = new_value;
			free(key);
			return;
		}
		envirement = envirement->next;
	}
	if(!identifier[plus_pos] || (identifier[plus_pos] && !identifier[plus_pos + 1]))
		new_value = ft_strdup("");
	else
		new_value = ft_substr(identifier, plus_pos + 2, ft_strlen(identifier + plus_pos + 2));
	ft_lstadd_back(env, ft_envlstnew(key, new_value));
}

void	export_new(t_env **env, int index, char *identifier){
	char *key;
	char *value;
	t_env *tmp_env = *env;

	key = ft_substr(identifier, 0, index);
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, key) == 0)
		{
			if(!identifier[index] || (identifier[index] && !identifier[index + 1]))
				value = ft_strdup("");
			else
				value = ft_substr(identifier, index + 1, ft_strlen(identifier + index));
			tmp_env->value = value;
			return ;
		}
		tmp_env = tmp_env->next;
	}
	if(!identifier[index] || (identifier[index] && !identifier[index + 1]))
		value = ft_strdup("");
	else
		value = ft_substr(identifier, index + 1, ft_strlen(identifier + index));
	ft_lstadd_back(env, ft_envlstnew(key, value));
}

void	export_to_env(t_env **env, char *identifier){
	int index = 0;

	while(identifier[index] && identifier[index] != '=' && identifier[index] != '+')
		index++;

	if(identifier[index] == '+')
		export_append(env, index, identifier);
	else
		export_new(env, index, identifier);
}

void	lets_export(t_env **env, char **args)
{
	int	index;

	index = true;
	while (args[index])
	{
		if(is_exportable(args[index]))
			export_to_env(env, args[index]);
		else
			printf(ERROR_MSG_IDENTIFIER);
		index++;
	}
}
