/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:23:27 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/09 17:36:37 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_alloc(t_entries *entries, t_philo **philos)
{
	*philos = malloc (sizeof(t_philo) * entries->num_philo);
	if (*philos == NULL)
		return (1);
	(*philos)[0].forks = malloc (sizeof(int) * entries->num_philo);
	if ((*philos)[0].forks == NULL)
	{
		free (philos);
		return (1);
	}
	(*philos)[0].mutex = malloc (sizeof(pthread_mutex_t));
	if ((*philos)[0].mutex == NULL)
	{
		free((*philos)[0].forks);
		free(*philos);
		return (1);
	}
	if (pthread_mutex_init((*philos)[0].mutex, NULL))
	{
		free((*philos)[0].mutex);
		free((*philos)[0].forks);
		free(*philos);
		return (1);
	}
	return (0);
}

int	init_values(t_entries *entries, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < entries->num_philo)
	{
		philos[0].forks[i] = 1;
		philos[i].forks = philos[0].forks;
		philos[i].entries = entries;
		philos[i].state = THINKING;
	}
	if (init_time(entries, philos))
	{
		pthread_mutex_destroy(philos[0].mutex);
		free(philos[0].mutex);
		free(philos[0].forks);
		free(philos);
		return (1);
	}
	return (0);
}

int	init_threads(t_entries *entries)
{
	t_philo			*philos;
	int				i;

	if (init_alloc(entries, &philos))
		return (1);
	pthread_mutex_lock(philos[0].mutex);
	i = -1;
	while (++i < entries->num_philo)
	{
		philos[i].id = i + 1;
		if (entries->num_to_eat != -1)
			philos[i].eat_left = entries->num_to_eat;
		else
			philos[i].eat_left = -1;
		philos[i].mutex = philos[0].mutex;
		pthread_create(&philos[i].thread, NULL, task, &philos[i]);
	}
	i = -1;
	if (init_values(entries, philos))
		return (1);
	pthread_mutex_unlock(philos[0].mutex);
	while (++i < entries->num_philo)
	{
		pthread_join(philos[i].thread, NULL);
		// pthread_mutex_lock(philos[0].mutex);
		// printf("\t\t%ld %d ends\n", get_ms_timestamp(), philos[i].id);
		// pthread_mutex_unlock(philos[0].mutex);
	}

	free(philos[0].mutex);
	free(philos[0].forks);
	free(philos);
	return (0);
}
