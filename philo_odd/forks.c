/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:42:55 by van               #+#    #+#             */
/*   Updated: 2025/04/11 16:19:13 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	int	i;
	int	j;
	int	time;

	i = philo->id - 1;
	j = philo->id;
	if (j == philo->entries->num_philo)
		j = 0;
	if (philo->forks[i] && philo->forks[j] && i != j)
	{
		philo->forks[i] = 0;
		philo->forks[j] = 0;
		time = philo->entries->time_to_eat * 1000;
		philo->state = HUNGRY;
		printf("%ld %d has taken a fork\n", get_ms_timestamp(), philo->id);
		printf("%ld %d has taken a fork\n", get_ms_timestamp(), philo->id);
		printf("%ld %d is eating\n", get_ms_timestamp(), philo->id);
		set_time(philo);
		pthread_mutex_unlock(philo->mutex);
		usleep(time);
	}
	else
	{
		// printf("\t\t%d can't take his fork\n", philo->id);
		pthread_mutex_unlock(philo->mutex);
		// usleep(INACTIVE_TIME);
		return (0);
	}
	return (0);
}

void	put_forks(t_philo *philo)
{
	int	i;
	int	j;

	i = philo->id - 1;
	j = philo->id;
	if (j == philo->entries->num_philo)
		j = 0;
	philo->forks[i] = 1;
	philo->forks[j] = 1;
	philo->state = EATING;
	if (philo->eat_left > 0)
		philo->eat_left--;
	pthread_mutex_unlock(philo->mutex);
	// act_prior(philo);
}
