/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:23:27 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/07 18:24:37 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*test(void *phil)
{
	t_philo *philo = (t_philo *)phil;
	// pthread_mutex_lock(philo->mutex);

	printf("Philo %d is doing something\n", philo->id);
	// pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

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
		philos[0].forks[i] = 1;
	if (set_time(entries, philos))
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
	i = -1;
	while (++i < entries->num_philo)
	{
		philos[i].id = i + 1;
		if (entries->num_to_eat != -1)
			philos[i].eat_left = entries->num_to_eat;
		else
			philos[i].eat_left = -1;
		philos[i].mutex = philos[0].mutex;
		pthread_create(&philos[i].thread, NULL, test, &philos[i]);
	}
	i = -1;
	if (init_values(entries, philos))
		return (1);
	while (++i < entries->num_philo)
	{
		pthread_join(philos[i].thread, NULL);
		printf("\tphilo %d die\n", philos[i].id);
	}
	free(philos[0].mutex);
	free(philos[0].forks);
	free(philos);
	return (0);
}
