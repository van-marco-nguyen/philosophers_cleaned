/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:11:50 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/21 17:06:51 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*task(void *arg)
{
	if (arg){}
	return (NULL);
}

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
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->mutex);
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

void	philo_routine(t_philo *philo)
{
	int	ret;

	pthread_detach(*philo->thread);
	while (1)
	{
		// printf("\t%d waits its mutex\n", philo->id);
		pthread_mutex_lock(philo->mutex);
		// printf("\t%d locked its mutex\n", philo->id);
		if (philo->end)
			break ;
		// printf("\t%d is going to do something\n", philo->id);
		// printf("\t%d unlocked its mutex\n", philo->id);
		pthread_mutex_unlock(philo->mutex);
		action(philo);
		// usleep(500000);
	}

	// printf("\t%d thread ends\n", philo->id);
	ret = philo->id;
	if (philo->eat_left == 0)
		ret = 0;
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_destroy(philo->mutex);
	// free(philo->mutex);
	// philo->mutex = NULL;
	free_philo(philo);
	exit (ret);
}
