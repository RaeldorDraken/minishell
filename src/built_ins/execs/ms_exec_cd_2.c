/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:39:21 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/30 20:41:02 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/mslib.h"

char	*msh_set_path(char *path, t_vars *vars)
{
	if (path == NULL)
		path = msh_get_env_value(vars, msh_get_env_index(vars, "PWD"));
	if (path[0] == '~')
		path = msh_get_env_value(vars, msh_get_env_index(vars, "HOME"));
	return (path);
}
