/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:57:34 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/21 17:01:05 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_time(t_philo *philo)
{
	t_timeval	now;

	if (gettimeofday(&now, NULL))
		return (err_gettimeofday_call());
	philo->tv->tv_sec = now.tv_sec;
	philo->tv->tv_usec = now.tv_usec;
	return (0);
}

long int	get_delay(t_timeval *tv)
{
	t_timeval	now;
	long int	sec_diff;
	long int	usec_diff;
	long int	ms;

	if (gettimeofday(&now, NULL))
		return (err_gettimeofday_call());
	sec_diff = now.tv_sec - tv->tv_sec;
	usec_diff = now.tv_usec - tv->tv_usec;
	ms = sec_diff * 1000;
	if (usec_diff < 0)
	{
		ms -= 1000;
		usec_diff = 1000000 + usec_diff;
	}
	ms += usec_diff / 1000;
	return (ms);
}

long int	get_ms_timestamp(void)
{
	static t_timeval	start;
	static int			initialized = 0;

	if (!initialized)
	{
		if (gettimeofday(&start, NULL))
			return (-1);
		initialized = 1;
	}
	return (get_delay(&start));
}

int	set_time(t_philo *philo)
{
	if (gettimeofday(philo->tv, NULL) == -1)
		return (err_gettimeofday_call());
	return (0);
}
