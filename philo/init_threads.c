/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:23:27 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/06 17:46:16 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*test(void *phil)
{
	t_philo *philo = (t_philo *)phil;
	printf("Philo %d is doing something\n", philo->id);
	return (NULL);
}

int	init_threads(t_entries *entries)
{
	t_philo		*philos;
	int			i;

	philos = malloc (sizeof(t_philo) * entries->num_philo);
	if (philos == NULL)
		return (1);
	i = -1;
	while (++i < entries->num_philo)
	{
		philos[i].id = i + 1;
		pthread_create(&philos[i].thread, NULL, test, &philos[i]);
	}
	i = -1;
	while (++i < entries->num_philo)
	{
		pthread_join(philos[i].thread, NULL);
		printf("\tphilo %d die\n", i + 1);
	}
	return (0);
}

// int	init_threads(t_entries *entries)
// {
// 	pthread_t	*threads;
// 	int			i;

// 	threads = malloc (sizeof(pthread_t) * entries->num_philo);
// 	if (threads == NULL)
// 		return (1);
// 	i = -1;
// 	while (++i < entries->num_philo)
// 	{
// 		pthread_create(&threads[i], NULL, NULL, NULL);
// 	}

// 	i = -1;
// 	while (++i < entries->num_philo)
// 	{
// 		pthread_join(threads[i], NULL);
// 	}
// 	return (0);
// }
