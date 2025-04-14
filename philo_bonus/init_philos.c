/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:32:29 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/14 18:25:52 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_abort(t_philo **philos)
{
	if (philos == NULL)
		return (1);
	while (1)
	{
		if (philos[0]->forks)
			free(philos[0]->forks);
		else
			break ;
		if (philos[0]->end)
			free(philos[0]->end);
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
		return (init_abort(philos));
	(*philos)[0].end = malloc(sizeof(int));
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

void	ftask(sem_t *sem, int id)
{
	sem_wait(sem);
	printf("%d gets semaphore\n", id);
	sem_post(sem);
}

int	init_philos(t_entries *entries)
{
	sem_t 	*sem;
	char	sem_name[] = "/philo_sem";

	sem = sem_open(sem_name, O_CREAT | O_EXCL, 0);
	// sem = sem_open(sem_name, O_CREAT, 0);
	if (sem == NULL)
	{
		printf("Can't open sem\n");
		return (1);
	}

	int	i = -1;
	int	pids[entries->num_philo - 1];
	while (++i < entries->num_philo)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			ftask(sem, i + 1);
			exit(0);
		}
		// exit(0);
	}
	waitpid(pids[i - 1], NULL, 0);
	printf("\tend\n");
	sem_close(sem);
	sem_unlink(sem_name);

	return (0);
}
