/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:42:55 by van               #+#    #+#             */
/*   Updated: 2025/04/23 16:57:53 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	int	time;

	sem_wait(philo->sem);
	pthread_mutex_lock(philo->mutex);
	time = philo->entries->time_to_eat * 1000;
	if (philo->entries->num_philo % 2 && philo->entries->num_philo < 4)
		time += philo->id * 1000;
	else if (philo->entries->num_philo % 2 && philo->entries->num_philo < 6)
		time += philo->id * 500;
	else if (philo->entries->num_philo % 2 && philo->entries->num_philo < 60)
		time += philo->id * 100;
	philo->state = HUNGRY;
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
		philo->end = 1;
}
