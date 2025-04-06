/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:09:02 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/06 15:48:10 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	isnum(char *s)
{
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (!('0' <= *s && *s <= '9'))
			return (0);
		s++;
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int	sum;
	int	sign;

	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	sum = 0;
	while (*s)
	{
		sum *= 10;
		sum += *s - '0';
		s++;
	}
	return (sum * sign);
}
