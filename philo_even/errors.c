/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van <van@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:41:53 by van-nguy          #+#    #+#             */
/*   Updated: 2025/04/09 17:21:31 by van              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	err_argc(int argc)
{
	if (argc < 5)
		write(2, "Too few arguments\n", 19);
	else if (argc > 6)
		write(2, "Too much arguments\n", 20);
	write(2, "\t1: number_of_philosophers\n", 28);
	write(2, "\t2: time_to_die (in milliseconds)\n", 35);
	write(2, "\t3: time_to_eat (in milliseconds)\n", 35);
	write(2, "\t4: time_to_sleep (in milliseconds)\n", 37);
	write(2, "\t5: number_of_times_each_philosopher_must_eat (optional)\n", 58);
	return (1);
}

int	err_argc_value(int i, int value)
{
	if (value < 0)
		write(2, "Cannot take negative value\n", 28);
	else
	{
		i += '0';
		write(2, "Too big value for argv[", 24);
		write(2, &i, 1);
		write(2, "]\n", 2);
	}
	return (1);
}

int	err_invalid_argv(int i)
{
	i += '0';
	write(2, "argv[", 6);
	write(2, &i, 1);
	write(2, "] is invalid\n", 14);
	return (1);
}

int	err_gettimeofday_call(void)
{
	write (2, "Error appended while calling gettimeofday()\n", 45);
	return (-1);
}
