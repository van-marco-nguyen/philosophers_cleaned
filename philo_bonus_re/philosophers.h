/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: van-nguy <van-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:20:53 by van               #+#    #+#             */
/*   Updated: 2025/04/18 17:23:23 by van-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define INACTIVE_TIME 1

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_entries
{
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_to_eat;
}				t_entries;

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	int				id;
	int				eat_left;
	t_timeval		*tv;
	int				state;
	t_entries		*entries;
	sem_t			*sem;
	char			sem_name[16];
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	int				end;
	pid_t			*pids;
	// int				dead;
	// int				*prior;
}				t_philo;

enum	e_state
{
	HUNGRY = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3
};

// errors.c
int			err_argc(int argc);
int			err_argc_value(int i, int value);
int			err_invalid_argv(int i);
int			err_gettimeofday_call(void);
int			err_malloc(void);

// s_entries.c
int			entries_init(t_entries *entries, int argc, char **argv);

// check_argv.c
int			check_argv(int argc, char **argv);

// init_philos.c
void		init_philos(t_entries *entries);
int			free_philo(t_philo *philo);

// time.c
long int	get_delay(t_timeval *tv);
int			init_time(t_philo *philo);
long int	get_ms_timestamp(void);
int			set_time(t_philo *philo);

// task.c
void		*task(void *arg);
void		*check_death(void *arg);
void		philo_routine(t_philo *philo);

// actions.c
int			do_die(t_philo *philo);
void		*do_sleep(t_philo *philo);
void		*do_eat(t_philo *philo);
void		*do_think(t_philo *philo);

// forks.c
int			take_forks(t_philo *philo);
void		put_forks(t_philo *philo);

// utils.c
int			ft_atoi(char *s);
int			isnum(char *s);
int			ft_strlcpy(char *dst, char *src, int size);

#endif
