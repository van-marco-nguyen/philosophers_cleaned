/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:09:01 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/14 16:36:40 by van-nguy         ###   ########.fr       */
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

void	*task_cond_if_1(t_philo *philo)
{
	act_prior(philo);
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

void	*task_cond_if_2(t_philo *philo)
{
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

void	*task(void *phil)
{
	int		delay;
	t_philo	*philo;

	philo = (t_philo *)phil;
	while (1)
	{
		pthread_mutex_lock(philo->mutex);
		if (*philo->end || philo->eat_left == 0)
			return (task_cond_if_1(philo));
		delay = get_delay(&philo->tv);
		if (delay == -1)
			task_cond_if_2(philo);
		if (delay >= philo->entries->time_to_die)
			return (do_die(philo));
		if (philo->entries->num_philo % 2 && !is_prior(philo))
		{
			pthread_mutex_unlock(philo->mutex);
			usleep(INACTIVE_TIME);
			continue ;
		}
		if (philo->entries->num_philo % 2)
			act_prior(philo);
		action(philo);
	}
	return (NULL);
}
