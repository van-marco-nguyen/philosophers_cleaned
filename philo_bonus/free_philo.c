/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:42:11 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/23 19:42:30 by van-nguy         ###   ########.fr       */
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
	if (philo->pids != NULL)
		free(philo->pids);
	if (philo->tv != NULL)
		free(philo->tv);
	return (1);
}
