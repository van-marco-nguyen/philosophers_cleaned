/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:09:01 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/08 17:24:22 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	action(t_philo *philo)
{
	if (philo->state == EATING)
		do_sleep(philo);
	else if (philo->state == SLEEPING)
		do_think(philo);
	else if (philo->state == THINKING)
		do_eat(philo);
	return (0);
}

void	*task(void *phil)
{
	int	delay;
	// pthread_mutex_lock(((t_philo *)phil)->mutex);
	t_philo *philo = (t_philo *)phil;
	pthread_mutex_lock(philo->mutex);
	if (philo->eat_left == 0)
	{
		pthread_mutex_unlock(philo->mutex);
		return (NULL);
	}
	if (philo->eat_left > 0)
		philo->eat_left--;
	delay = get_delay(&philo->tv);
	// printf("\tdelay: %d\n", delay);
	if (delay == -1)
	{
		printf("error occurs\n");
		pthread_mutex_unlock(philo->mutex);
		return (NULL);
	}
	if (delay >= philo->entries->time_to_die)
		return (do_die(philo));
	action(philo);
	// if (philo->id)
	// {
	// 	printf("%ld %d is doing something\n", get_ms_timestamp(), philo->id);
	// }
	// pthread_mutex_unlock(philo->mutex);
	return (task(phil));
}
