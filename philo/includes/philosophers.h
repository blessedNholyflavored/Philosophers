/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <lkhamlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:25:08 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/02/16 16:55:43 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIE "died"

# define INT_MAX 2147483647

typedef struct s_args
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	int		compteurphilo;
}	t_args;

typedef struct s_fork
{
	int		right;
	int		left;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			number_of_times_each_philosopher_ate;
	long long	time_to_die;
	t_fork		fork;
	pthread_t	thread;
}	t_philo;

typedef struct s_master
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	int				deadphilosopher;
	int				nb_thread;
	long long		time;
	t_args			args;
	pthread_t		thread2;
	pthread_mutex_t	nbmutex;
	pthread_mutex_t	already_ate;
	pthread_mutex_t	dead;
	pthread_mutex_t	timemutex;
}	t_master;

// truc important
int			add_philo(t_master *master);
int			add_forks(t_master *master);
int			philo_print(t_master *master, int id, char *status);

// one philo
int			onlyonephilo(t_master *master);

//temps
void		actions_time(long long time);
long long	what_time_is_it(void);
long long	current_time(long long time);//, t_master *master);

//philo doing shit
int			sleepingphilo(t_master *master, int i);
int			thinkingphilo(t_master *master, int i);
int			eatingphilo(t_master *master, int i);
int			drop_the_fork(t_master *master, int i);
int			dyingphilo(t_master *master, int *i);

//utils
void		ft_free(t_master *master);
int			ft_atoi(const char *str);

// panic thread
void		*checker(void *args);
int			join_threads(t_master *master);
int			execution_routine(t_master *master, int i);
void		*routine(void *args);
int			destroy_threads(t_master *master);
int			init_thread(t_master *master);

//check
int			check_ate(t_master *master, int i);
int			checkdead(t_master *master);

#endif
