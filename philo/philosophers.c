/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:20:12 by van               #+#    #+#             */
/*   Updated: 2025/04/06 17:30:15 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_entries entries;

	if (argc != 5 && argc != 6)
		return (err_argc(argc));

	if (entries_init(&entries, argc, argv))
		return (1);

	init_threads(&entries);

	return (0);
	if (argc || argv)
		;
}

