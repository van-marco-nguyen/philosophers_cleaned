/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:20:53 by van               #+#    #+#             */
/*   Updated: 2025/04/07 18:21:26 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_entries
{
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_to_eat;
}				t_entries;

typedef	struct timeval	t_timeval;

typedef struct s_philo
{
	int				id;
	int				eat_left;
	pthread_mutex_t	*mutex;
	int				*forks;
	pthread_t		thread;
	t_timeval		tv;
}				t_philo;

// errors.c
int			err_argc(int argc);
int			err_argc_value(int i, int value);
int			err_invalid_argv(int i);
int			err_gettimeofday_call(void);

// s_entries.c
int			entries_init(t_entries *entries, int argc, char **argv);

// check_argv.c
int			check_argv(int argc, char **argv);

// init_threads.c
int			init_threads(t_entries *entries);

// time.c
long int	get_delay(t_timeval *tv);
int			set_time(t_entries *entries, t_philo *philos);

// utils.c
int			ft_atoi(char *s);
int			isnum(char *s);

#endif
