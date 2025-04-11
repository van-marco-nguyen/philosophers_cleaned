/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:09:01 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/11 16:19:32 by van-nguy         ###   ########.fr       */
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

void	*task(void *phil)
{
	int	delay;
	t_philo *philo = (t_philo *)phil;

	while (1)
	{
		pthread_mutex_lock(philo->mutex);
		if (*philo->end || philo->eat_left == 0)
		{
			act_prior(philo);
			pthread_mutex_unlock(philo->mutex);
			return (NULL);
		}
		delay = get_delay(&philo->tv);
		if (delay == -1)
		{
			printf("error occured\n");
			pthread_mutex_unlock(philo->mutex);
			return (NULL);
		}
		if (delay >= philo->entries->time_to_die)
			return (do_die(philo));
		if (philo->entries->num_philo % 2 && !is_prior(philo))
		{
			pthread_mutex_unlock(philo->mutex);
			usleep(INACTIVE_TIME);
			continue;
		}
		// printf("\t\tprior: %d - %d, id: %d\n", philo->prior[0], philo->prior[1], philo->id);
		if (philo->entries->num_philo % 2)
			act_prior(philo);
		action(philo);
	}
	return (NULL);
}

// void *task(void *phil) {
//     t_philo *philo = (t_philo *)phil;

//     while (1) {
//         pthread_mutex_lock(philo->mutex);
//         if (philo->eat_left == 0) {
//             pthread_mutex_unlock(philo->mutex);
//             break;
//         }
//         long int delay = get_delay(&philo->tv);
//         if (delay == -1 || delay >= philo->entries->time_to_die) {
//             printf("%ld %d died\n", get_ms_timestamp(), philo->id);
//             pthread_mutex_unlock(philo->mutex);
//             break;
//         }
//         action(philo);
//         // pthread_mutex_unlock(philo->mutex);
//     }
//     return NULL;
// }
