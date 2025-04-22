/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:09:17 by van               #+#    #+#             */
/*   Updated: 2025/04/22 14:22:28 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	int_len(int n)
{
	int	len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	write_id(int id, int i, char *str_id)
{
	if (i == 0)
		str_id[0] = id + '0';
	else
	{
		str_id[i] = id % 10 + '0';
		write_id(id / 10, i - 1, str_id);
	}
}

void cat_id(int id, char *src)
{
	char	id_str[5];

	memset(id_str, '\0', 5);
	write_id(id, int_len(id) - 1, id_str);
	while (*src)
		src++;
	ft_strlcpy(src, id_str, 5);
}

int	init_sem(t_philo *philo)
{
	ft_strlcpy(philo->sem_name, "philo_sem", 10);
	ft_strlcpy(philo->sem_name_2, "philo_sem", 10);
	if (philo->id == philo->entries->num_philo)
	{
		cat_id(1, philo->sem_name);
		cat_id(philo->id, philo->sem_name_2);
	}
	else
	{
		cat_id(philo->id, philo->sem_name);
		cat_id(philo->id + 1, philo->sem_name_2);
	}
	printf("%d: %s %s\n", philo->id, philo->sem_name, philo->sem_name_2);
	philo->sem = sem_open(philo->sem_name, O_CREAT, 0666, 1);
	philo->sem_2 = sem_open(philo->sem_name_2, O_CREAT, 0666, 1);
	if (philo->sem == SEM_FAILED || philo->sem_2 == SEM_FAILED)
	{
		perror("sem_open");
		return (free_philo(philo));
	}
	return (0);
}
