/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:57:10 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/08 17:35:36 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*do_die(t_philo *philo)
{
	printf("%ld %d died\n", get_ms_timestamp(), philo->id);
	printf("\tdelay > ttd=%d\n", philo->entries->time_to_die);
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

void	*do_sleep(t_philo *philo)
{
	int	sleep;

	sleep = philo->entries->time_to_sleep;
	philo->state = SLEEPING;
	printf("%ld %d is sleeping\n", get_ms_timestamp(), philo->id);
	// printf("\t\tsleep: %d\n", sleep);
	pthread_mutex_unlock(philo->mutex);
	usleep(sleep);
	return (NULL);
}

void	*do_eat(t_philo *philo)
{
	int	time;

	time = philo->entries->time_to_eat;
	philo->state = EATING;
	printf("%ld %d is eating\n", get_ms_timestamp(), philo->id);
	// printf("\t\time: %d\n", time);
	pthread_mutex_unlock(philo->mutex);
	usleep(time);
	return (NULL);
}

void	*do_think(t_philo *philo)
{

	philo->state = THINKING;
	printf("%ld %d is thinking\n", get_ms_timestamp(), philo->id);
	// printf("\t\time: %d\n", time);
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}
