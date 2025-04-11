/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:23:27 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/11 17:56:29 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_abort(t_philo **philos)
{
	if (philos == NULL)
		return (1);
	while (1)
	{
		if (philos[0]->end)
			free(philos[0]->end);
		else
			break ;
		if (philos[0]->forks)
			free(philos[0]->forks);
		else
			break ;
		if (philos[0]->prior)
			free(philos[0]->prior);
		else
			break ;
		if (philos[0]->mutex)
			free(philos[0]->mutex);
		break ;
	}
	free(*philos);
	return (1);
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
	(*philos)[0].end = malloc(sizeof(int));
	// (*philos)[0].end = NULL;
	if ((*philos)[0].end == NULL)
		return (init_abort(philos));
	(*philos)[0].prior = malloc(sizeof(int) * 4);
	if ((*philos[0]).prior == NULL)
		return (init_abort(philos));
	(*philos)[0].mutex = malloc (sizeof(pthread_mutex_t));
	if ((*philos)[0].mutex == NULL)
		return (init_abort(philos));
	if (pthread_mutex_init((*philos)[0].mutex, NULL))
		return (init_abort(philos));
	return (0);
}

// int	init_alloc(t_entries *entries, t_philo **philos)
// {
// 	*philos = malloc (sizeof(t_philo) * entries->num_philo);
// 	if (*philos == NULL)
// 		return (1);
// 	(*philos)[0].forks = malloc (sizeof(int) * entries->num_philo);
// 	if ((*philos)[0].forks == NULL)
// 	{
// 		free (philos);
// 		return (1);
// 	}
// 	(*philos)[0].end = malloc(sizeof(int));
// 	if ((*philos)[0].end == NULL)
// 	{
// 		free((*philos)[0].forks);
// 		free(philos);
// 		return (1);
// 	}
// 	(*philos)[0].prior = malloc(sizeof(int) * 4);
// 	if ((*philos[0]).prior == NULL)
// 	{
// 		free((*philos)[0].end);
// 		free((*philos)[0].forks);
// 		free(philos);
// 		return (1);
// 	}
// 	(*philos)[0].mutex = malloc (sizeof(pthread_mutex_t));
// 	if ((*philos)[0].mutex == NULL)
// 	{
// 		free((*philos)[0].end);
// 		free((*philos)[0].forks);
// 		free((*philos)[0].prior);
// 		free(*philos);
// 		return (1);
// 	}
// 	if (pthread_mutex_init((*philos)[0].mutex, NULL))
// 	{
// 		free((*philos)[0].end);
// 		free((*philos)[0].prior);
// 		free((*philos)[0].mutex);
// 		free((*philos)[0].forks);
// 		free(*philos);
// 		return (1);
// 	}
// 	return (0);
// }

int	init_values(t_entries *entries, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < entries->num_philo)
	{
		philos[0].forks[i] = 1;
		philos[i].end = philos[0].end;
		philos[i].forks = philos[0].forks;
		philos[i].entries = entries;
		philos[i].prior = philos[0].prior;
		philos[i].state = THINKING;
	}
	*philos[0].end = 0;
	i = -1;
	while (++i < 4)
		philos[0].prior[i] = 0;
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

void	free_philos(t_philo *philos)
{
	if (philos[0].end != NULL)
		free(philos[0].end);
	if (philos[0].prior != NULL)
		free(philos[0].prior);
	if (philos[0].mutex != NULL)
		free(philos[0].mutex);
	if (philos[0].forks != NULL)
		free(philos[0].forks);
	free(philos);
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
		philos[i].eat_left = -1;
		if (entries->num_to_eat != -1)
			philos[i].eat_left = entries->num_to_eat;
		philos[i].mutex = philos[0].mutex;
		pthread_create(&philos[i].thread, NULL, task, &philos[i]);
	}
	i = -1;
	if (init_values(entries, philos))
		return (1);
	get_ms_timestamp();
	pthread_mutex_unlock(philos[0].mutex);
	while (++i < entries->num_philo)
		pthread_join(philos[i].thread, NULL);
	free_philos(philos);
	return (0);
}
