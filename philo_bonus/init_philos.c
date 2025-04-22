/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:10:42 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/22 15:56:38 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_philo(t_philo *philo)
{
	if (philo->thread != NULL)
		free(philo->thread);
	if (philo->mutex != NULL)
		free(philo->mutex);
	if (philo->sem != NULL && philo->sem != SEM_FAILED)
		sem_close(philo->sem);
	if (philo->sem_2 != NULL && philo->sem_2 != SEM_FAILED)
		sem_close(philo->sem_2);
	if (philo->pids != NULL)
		free(philo->pids);
	if (philo->tv != NULL)
		free(philo->tv);
	return (1);
}

int	init_allocs(t_philo *philo, t_entries *entries)
{
	philo->mutex = NULL;
	philo->thread = NULL;
	philo->sem = NULL;
	philo->sem_2 = NULL;
	philo->pids = NULL;
	philo->tv = NULL;

	philo->mutex = malloc(sizeof(pthread_mutex_t));
	if (philo->mutex == NULL)
		return (free_philo(philo));
	philo->thread = malloc(sizeof(pthread_t));
	if (philo->thread == NULL)
		return (free_philo(philo));
	philo->pids = malloc (sizeof(pid_t) * entries->num_philo);
	if (philo->pids == NULL)
		return (free_philo(philo));
	philo->tv = malloc (sizeof(t_timeval));
	if (philo->tv == NULL)
		return (free_philo(philo));
	return (0);
}

int	init_values(t_entries *entries, t_philo *philo)
{
	philo->entries = entries;
	philo->eat_left = entries->num_to_eat;
	philo->end = 0;
	philo->state = THINKING;
	ft_strlcpy(philo->sem_name, "/philo_sem", 11);
	if (pthread_mutex_init(philo->mutex, NULL))
		return (free_philo(philo));
	// philo->sem = sem_open(philo->sem_name, O_CREAT | O_EXCL, 0644, entries->num_philo / 2);
	// if (philo->sem == SEM_FAILED)
	// {
	// 	perror("sem_open");
	// 	sem_unlink(philo->sem_name);
	// 	return (free_philo(philo));
	// }
	return (0);
}

void	unlink_sem(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo->entries->num_philo)
	{
		ft_strlcpy(philo->sem_name, "philo_sem", 10);
		cat_id(i, philo->sem_name);
		printf("unlink %s\n", philo->sem_name);
		sem_unlink(philo->sem_name);
	}
}

void	init_philos(t_entries *entries)
{
	t_philo		philo;
	int			i;
	int			status;

	if (init_allocs(&philo, entries))
		return ;
	if (init_values(entries, &philo))
		return ;
	unlink_sem(&philo);

	// pthread_mutex_lock(philo.mutex);
	get_ms_timestamp();
	set_time(&philo);
	i = -1;
	while (++i < entries->num_philo)
	{
		philo.pids[i] = fork();
		if (philo.pids[i] == -1){}
		else if (philo.pids[i] == 0)
		{
			philo.id = i + 1;
			if (init_sem(&philo))
				exit(free_philo(&philo));
			if (pthread_create(philo.thread, NULL, check_death, &philo))
			{
				// pthread_mutex_unlock(philo.mutex);
				// pthread_mutex_destroy(philo.mutex);
				free_philo(&philo);
				exit (0);
			}
			philo_routine(&philo);
			printf("philo %d ends shouldn't have reach that line\n", philo.id);
		}
	}
	// pthread_mutex_unlock(philo.mutex);

	i = -1;
	while (++i < entries->num_philo)
	{
		wait(&status);
		if (status)
		{
			i = -1;
			while (++i < entries->num_philo)
			{
				if (i == status - 1)
					continue ;
				kill(philo.pids[i], 9);
			}
		}
	}

	pthread_mutex_destroy(philo.mutex);
	// sem_unlink(philo.sem_name);
	unlink_sem(&philo);
	free_philo(&philo);
	printf("reach end\n");
}

