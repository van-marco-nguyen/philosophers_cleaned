/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:32:29 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/15 17:31:21 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_values(t_entries *entries, t_philo *philo, sem_t *sem, t_timeval *tv)
{
	philo->state = THINKING;
	philo->entries = entries;
	philo->sem = sem;
	philo->eat_left = entries->num_to_eat;
	philo->tv = *tv;
	if (gettimeofday(&philo->tv, NULL))
		return (1);
	return (0);
}

int	init_philos(t_entries *entries)
{
	sem_t 	*sem;
	char	sem_name[] = "/philo_sem";

	sem = sem_open(sem_name, O_CREAT | O_EXCL, 0, entries->num_philo / 2);
	// sem = sem_open(sem_name, O_CREAT, 0);
	if (sem == NULL)
	{
		printf("Can't open sem\n");
		sem_unlink(sem_name);
		return (1);
	}

	t_philo		philo;
	t_timeval	tv;
	init_values(entries, &philo, sem, &tv);
	get_ms_timestamp();
	// if (gettimeofday(&philo.tv, NULL))
	// 	return (err_gettimeofday_call());
	int	i = -1;
	int	pids[entries->num_philo - 1];
	while (++i < entries->num_philo)
	{
		philo.id = i + 1;
		pids[i] = fork();
		if (pids[i] == 0)
		{
			task(&philo);
			exit(0);
		}
		// exit(0);
	}

	int	status;
	i = -1;
	while (++i < entries->num_philo)
	{
		wait(&status);
		if (status)
		{
			printf("status: %d\n", status);
			i = -1;
			while (++i < entries->num_philo)
			{
				kill(pids[i], 9);
				printf("kill %d\n", i + 1);
			}


			break ;
		}
	}
	printf("\tend\n");
	sem_close(sem);
	sem_unlink(sem_name);

	return (0);
}
