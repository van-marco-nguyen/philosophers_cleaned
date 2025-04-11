/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:57:10 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/11 16:25:20 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*do_die(t_philo *philo)
{
	printf("%ld %d died\n", get_ms_timestamp(), philo->id);
	*philo->end = 1;
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

void	*do_sleep(t_philo *philo)
{
	int	sleep;

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
	pthread_mutex_unlock(philo->mutex);
	usleep(time);
	return (NULL);
}

void	*do_think(t_philo *philo)
{
	philo->state = THINKING;
	printf("%ld %d is thinking\n", get_ms_timestamp(), philo->id);
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}
