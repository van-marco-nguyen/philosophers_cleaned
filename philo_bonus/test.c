/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:32:29 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/15 12:26:50 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ftask(sem_t *sem, int id)
{
	sem_wait(sem);
	printf("%d gets semaphore\n", id);
	usleep(1000000);
	sem_post(sem);
}

int	main(int argc, char **argv)
{
	int		num_philo;
	sem_t 	*sem;
	char	sem_name[] = "/philo_sem";

	if (argc > 1)
	{
		num_philo = ft_atoi(argv[1]);
		if (num_philo == 0)
			return (0);

		sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, num_philo / 2);
		// sem = sem_open(sem_name, O_CREAT, 0);
		if (sem == NULL)
		{
			printf("Can't open sem\n");
			return (1);
		}

		int	i = -1;
		int	pids[num_philo - 1];
		while (++i < num_philo)
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
	}
	return (0);
}
