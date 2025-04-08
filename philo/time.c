/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:57:34 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/08 15:26:04 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	set_time(t_entries *entries, t_philo *philos)
{
	int			i;
	t_timeval	now;

	if (gettimeofday(&now, NULL))
		return (err_gettimeofday_call());
	i = -1;
	while (++i < entries->num_philo)
	{
		philos[i].tv.tv_sec = now.tv_sec;
		philos[i].tv.tv_usec = now.tv_usec;
	}
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
	t_timeval	now;

	if (gettimeofday(&now, NULL))
		return (err_gettimeofday_call());
	return (now.tv_usec / 1000);
}
