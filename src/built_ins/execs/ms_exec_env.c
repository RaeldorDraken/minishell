/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:21:04 by rabril-h          #+#    #+#             */
/*   Updated: 2023/07/30 19:49:03 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

int	msh_get_env_vars_length(t_vars *vars)
{
	int	c;

	c = 0;
	while (vars->envar && vars->envar[c])
		c++;
	return (c);
}

int	msh_is_valid_env_var_key(char *var_name)
{
	int	i;

	i = 0;
	if (ft_isalpha(var_name[i]) == 0 && var_name[i] != '_')
		return (0);
	i++;
	while (var_name[i] && var_name[i] != '=')
	{
		if (ft_isalnum(var_name[i]) == 0 && var_name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	msh_exec_env(t_cmd *cmd, t_vars *vars)
{
	int	env_length;

	env_length = -1;
	if (cmd->argv && cmd->argv[1])
		ft_putendl_fd("env: Too many arguments for minishell", 2);
	else
		msh_print_env_vars(vars, "");
}
