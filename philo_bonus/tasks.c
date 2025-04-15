/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:09:01 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/15 17:27:01 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	action(t_philo *philo)
{
	if (philo->state == THINKING)
		take_forks(philo);
	else if (philo->state == HUNGRY)
		put_forks(philo);
	else if (philo->state == EATING)
		do_sleep(philo);
	else if (philo->state == SLEEPING)
		do_think(philo);
	return (0);
}

int	task(t_philo *philo)
{
	while (1)
	{
		if (philo->eat_left == 0)
		{
			break ;
		}
		if (get_delay(&philo->tv) >= philo->entries->time_to_die)
			return (do_die(philo));
		action(philo);
		// usleep(100000);
	}
	sem_close(philo->sem);
	return (0);
}
