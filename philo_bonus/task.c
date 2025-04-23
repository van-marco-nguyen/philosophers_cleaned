/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:11:50 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/23 19:36:25 by van-nguy         ###   ########.fr       */
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

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->mutex);
		if (philo->end == 1)
			break ;
		if (get_delay(philo->tv) >= philo->entries->time_to_die)
		{
			do_die(philo);
			break ;
		}
		pthread_mutex_unlock(philo->mutex);
		usleep(1000);
	}
	return (NULL);
}

void	lonely_philo(t_philo *philo)
{
	printf("%ld %d has taken a fork\n", get_ms_timestamp(), philo->id);
	usleep(philo->entries->time_to_die * 1000 + 1000);
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_destroy(philo->mutex);
	pthread_join(*philo->thread, NULL);
	exit (free_philo(philo));
}

void	philo_routine(t_philo *philo)
{
	int	ret;

	if (philo->entries->num_philo == 1)
		lonely_philo(philo);
	while (1)
	{
		pthread_mutex_lock(philo->mutex);
		if (philo->end)
			break ;
		pthread_mutex_unlock(philo->mutex);
		action(philo);
	}
	ret = philo->id;
	if (philo->eat_left == 0)
		ret = 0;
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_destroy(philo->mutex);
	pthread_join(*philo->thread, NULL);
	free_philo(philo);
	exit (ret);
}
