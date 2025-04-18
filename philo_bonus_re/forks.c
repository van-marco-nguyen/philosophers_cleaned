/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:42:55 by van               #+#    #+#             */
/*   Updated: 2025/04/18 16:30:06 by van-nguy         ###   ########.fr       */
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
	time = philo->entries->time_to_eat * 1000;
	philo->state = HUNGRY;
	sem_wait(philo->sem);
	if (get_delay(philo->tv) >= philo->entries->time_to_die)
		return (do_die(philo));
	printf("%ld %d has taken a fork\n", get_ms_timestamp(), philo->id);
	printf("%ld %d has taken a fork\n", get_ms_timestamp(), philo->id);
	printf("%ld %d is eating\n", get_ms_timestamp(), philo->id);
	set_time(philo);
	usleep(time);
	return (0);
}

void	put_forks(t_philo *philo)
{
	sem_post(philo->sem);
	philo->state = EATING;
	if (philo->eat_left > 0)
		philo->eat_left--;
}
