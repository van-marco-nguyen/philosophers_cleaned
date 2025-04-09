/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:42:55 by van               #+#    #+#             */
/*   Updated: 2025/04/09 17:38:23 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	printf("\t\t%d entering take_forks()\n", philo->id);
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
		time = philo->entries->time_to_eat;
		philo->state = HUNGRY;
		printf("%ld %d has taken a fork\n", get_ms_timestamp(), philo->id);
		set_time(philo);
		pthread_mutex_unlock(philo->mutex);
		usleep(time);
	}
	else
	{
		pthread_mutex_unlock(philo->mutex);
		usleep(INACTIVE_TIME);
		return (1);
	}
	return (0);
}

void	put_forks(t_philo *philo)
{
	printf("\t\t%d entering put_forks()\n", philo->id);
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
	set_time(philo);
	printf("%ld %d is eating\n", get_ms_timestamp(), philo->id);
	pthread_mutex_unlock(philo->mutex);
}
