/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_doing_stuff.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <lkhamlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:24:00 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/02/16 16:48:40 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleepingphilo(t_master *master, int i)
{
	philo_print(master, master->philo[i].id, SLEEP);
	actions_time(master->args.time_to_sleep);
	return (1);
}

int	thinkingphilo(t_master *master, int i)
{
	philo_print(master, master->philo[i].id, THINK);
	return (1);
}

int	eatingphilo(t_master *master, int i)
{
	if (i % 2 == 0)
	{
		pthread_mutex_lock(&master->forks[master->philo[i].fork.left]);
		philo_print(master, master->philo[i].id, FORK);
		pthread_mutex_lock(&master->forks[master->philo[i].fork.right]);
		philo_print(master, master->philo[i].id, FORK);
	}
	else
	{
		pthread_mutex_lock(&master->forks[master->philo[i].fork.right]);
		philo_print(master, master->philo[i].id, FORK);
		pthread_mutex_lock(&master->forks[master->philo[i].fork.left]);
		philo_print(master, master->philo[i].id, FORK);
	}
	philo_print(master, master->philo[i].id, EAT);
	pthread_mutex_lock(&master->timemutex);
	master->philo[i].time_to_die = what_time_is_it();
	pthread_mutex_unlock(&master->timemutex);
	actions_time(master->args.time_to_eat);
	drop_the_fork(master, i);
	return (1);
}

int	drop_the_fork(t_master *master, int i)
{
	if (i % 2 == 0)
	{
		pthread_mutex_unlock(&master->forks[master->philo[i].fork.left]);
		pthread_mutex_unlock(&master->forks[master->philo[i].fork.right]);
	}
	else
	{
		pthread_mutex_unlock(&master->forks[master->philo[i].fork.right]);
		pthread_mutex_unlock(&master->forks[master->philo[i].fork.left]);
	}
	pthread_mutex_lock(&master->already_ate);
	master->philo[i].number_of_times_each_philosopher_ate++;
	pthread_mutex_unlock(&master->already_ate);
	return (1);
}

int	philo_print(t_master *master, int id, char *status)
{
	long long	now;

	now = current_time(master->time);
	if (checkdead(master) == 1)
		return (0);
	pthread_mutex_lock(&master->write);
	if (checkdead(master) == 1)
	{
		pthread_mutex_unlock(&master->write);
		return (0);
	}
	else
		printf("%-10lld philosopher %d %s\n", now, id, status);
	pthread_mutex_unlock(&master->write);
	return (1);
}
