/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_entries.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:53:50 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/08 15:40:48 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	entries_init(t_entries *entries, int argc, char **argv)
{
	if (check_argv(argc, argv))
		return (1);
	entries->num_philo = ft_atoi(argv[1]);
	entries->time_to_die = ft_atoi(argv[2]);
	entries->time_to_eat = ft_atoi(argv[3]);
	entries->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		entries->num_to_eat = ft_atoi(argv[5]);
	else
		entries->num_to_eat = -1;
	return (0);
}
