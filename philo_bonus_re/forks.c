/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:42:55 by van               #+#    #+#             */
/*   Updated: 2025/04/21 19:32:21 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	int	time;

	// while (!is_prior(philo))
	// {
	// 	usleep(INACTIVE_TIME);
	// }
	sem_wait(philo->sem);
	// act_prior(philo);
	pthread_mutex_lock(philo->mutex);
	time = philo->entries->time_to_eat * 1000;
	philo->state = HUNGRY;
	// if (get_delay(philo->tv) >= philo->entries->time_to_die)
	// 	return (do_die(philo));
	if (philo->end == 1)
	{
		pthread_mutex_unlock(philo->mutex);
		return (0);
	}
	printf("%ld %d has taken a fork\n", get_ms_timestamp(), philo->id);
	printf("%ld %d has taken a fork\n", get_ms_timestamp(), philo->id);
	printf("%ld %d is eating\n", get_ms_timestamp(), philo->id);
	set_time(philo);
	pthread_mutex_unlock(philo->mutex);
	usleep(time);
	sem_post(philo->sem);
	return (0);
}

void	put_forks(t_philo *philo)
{
	philo->state = EATING;
	if (philo->eat_left > 0)
		philo->eat_left--;
	if (philo->eat_left == 0)
	{
		philo->end = 1;
	}

}
