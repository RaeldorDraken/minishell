/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:25:03 by eros-gir          #+#    #+#             */
/*   Updated: 2023/07/30 19:51:44 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_isalpha(int c)
{
	int	res;

	res = 0;
	if (c >= 65 && c <= 122)
	{
		res = 1;
		if (c >= 91 && c <= 96)
			res = 0;
	}
	return (res);
}