/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:20:12 by van               #+#    #+#             */
/*   Updated: 2025/04/18 13:13:09 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// valgrind --tool=helgrind		//err threads

int	main(int argc, char **argv)
{
	t_entries	entries;

	if (argc != 5 && argc != 6)
		return (err_argc(argc));
	if (entries_init(&entries, argc, argv))
		return (1);
	if (entries.num_philo != 0)
		init_philos(&entries);
	return (0);
}
