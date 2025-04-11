/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prior.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:10:15 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/11 14:58:38 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_prior(t_philo *philo)
{
	if (philo->id == philo->entries->num_philo)
	{
		if (philo->prior[0] == 2)
			return (1);
		return (0);
	}
	if (philo->id % 2 == philo->prior[0])
		return (1);
	return (0);
}

void	act_prior_group(int *prior, int *num_odd, int *num_even, int *last)
{
	if (prior[0] == 0 && prior[1] == *num_even)
	{
		prior[1] = 0;
		prior[0] = 1;
	}
	if (prior[0] == 1 && prior[2] == *num_odd)
	{
		prior[2] = 0;
		prior[0] = 2;
	}
	if (prior[0] == 2 && prior[3] == *last)
	{
		prior[3] = 0;
		prior[0] = 0;
	}
}

void	act_prior(t_philo *philo)
{
	static int	num_odd = -1;
	static int	num_even = -1;
	static int	last = -1;

	if (num_odd == -1)
	{
		num_even = philo->entries->num_philo / 2;
		num_odd = philo->entries->num_philo / 2;
		last = 1;
	}
	if (philo->eat_left == 0)
	{
		if (philo->id == philo->entries->num_philo)
			last--;
		else if (philo->id % 2)
			num_even--;
		else
			num_odd--;
		// printf("\t\t%d ends remain: %d %d %d\n", philo->id, num_odd, num_even, last);
		act_prior_group(philo->prior, &num_even, &num_odd, &last);
		return ;
	}
	if (philo->state == EATING)
	{
		if (philo->id == philo->entries->num_philo)
			philo->prior[3]++;
		else if (philo->id % 2)
			philo->prior[2]++;
		else
			philo->prior[1]++;
	}

	act_prior_group(philo->prior, &num_even, &num_odd, &last);

	// if (philo->state == EATING)
	// 	(philo->prior[1])++;
	// if (philo->prior[1] == philo->entries->num_philo / 2)
	// {
	// 	philo->prior[1] = 0;
	// 	if (philo->prior[0] == 0)
	// 		philo->prior[0] = 1;
	// 	else if (philo->prior[0] == 1)
	// 		philo->prior[0] = 2;
	// 	else
	// 		philo->prior[0] = 0;
	// }
	// else if (philo->prior[0] == 2 && philo->prior[1] == 1)
	// {
	// 	philo->prior[1] = 0;
	// 	philo->prior[0] = 0;
	// }
}
