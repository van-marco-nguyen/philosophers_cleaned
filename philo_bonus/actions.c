/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:57:10 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/23 16:57:37 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	do_die(t_philo *philo)
{
	int	ret;

	printf("%ld %d died\n", get_ms_timestamp(), philo->id);
	ret = philo->id;
	philo->end = 1;
	pthread_mutex_unlock(philo->mutex);
	return (ret);
}

void	*do_sleep(t_philo *philo)
{
	int	sleep;

	pthread_mutex_lock(philo->mutex);
	sleep = philo->entries->time_to_sleep * 1000;
	philo->state = SLEEPING;
	printf("%ld %d is sleeping\n", get_ms_timestamp(), philo->id);
	pthread_mutex_unlock(philo->mutex);
	usleep(sleep);
	return (NULL);
}

void	*do_eat(t_philo *philo)
{
	int	time;

	time = philo->entries->time_to_eat * 1000;
	philo->state = EATING;
	printf("%ld %d is eating\n", get_ms_timestamp(), philo->id);
	usleep(time);
	return (NULL);
}

void	*do_think(t_philo *philo)
{
	philo->state = THINKING;
	printf("%ld %d is thinking\n", get_ms_timestamp(), philo->id);
	return (NULL);
}
