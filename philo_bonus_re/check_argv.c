/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:43:02 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/06 16:03:35 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_argv(int argc, char **argv)
{
	int	i;
	int	value;

	i = 0;
	while (++i < argc)
	{
		value = ft_atoi(argv[i]);
		if (!isnum(argv[i]))
			return (err_invalid_argv(i));
		if (value < 0 || value > 1000)
			return (err_argc_value(i, value));
		if (i == 1 && value > 100)
			return (err_argc_value(i, value));
	}
	return (0);
}
