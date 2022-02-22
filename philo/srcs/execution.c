/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <lkhamlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:13:06 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/02/16 16:45:28 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_ate(t_master *master, int i)
{
	pthread_mutex_lock(&master->already_ate);
	if (master->args.number_of_times_each_philosopher_must_eat
		> master->philo[i].number_of_times_each_philosopher_ate
		&& master->deadphilosopher == 0)
	{
		pthread_mutex_unlock(&master->already_ate);
		return (-1);
	}
	pthread_mutex_unlock(&master->already_ate);
	return (0);
}

int	checkdead(t_master *master)
{
	pthread_mutex_lock(&master->dead);
	if (master->deadphilosopher == 0)
	{
		pthread_mutex_unlock(&master->dead);
		return (0);
	}
	pthread_mutex_unlock(&master->dead);
	return (1);
}

void	*routine(void *args)
{
	t_master	*master;
	int			i;

	master = (t_master *)args;
	pthread_mutex_lock(&master->nbmutex);
	i = master->nb_thread;
	pthread_mutex_unlock(&master->nbmutex);
	if (master->args.number_of_times_each_philosopher_must_eat > 0)
	{
		while ((check_ate(master, i) == -1) && (checkdead(master) == 0))
			execution_routine(master, i);
	}
	else
	{
		while (checkdead(master) == 0)
		{
			if (execution_routine(master, i) == 0)
				break ;
		}
	}
	return (NULL);
}

int	execution_routine(t_master *master, int i)
{
	if (eatingphilo(master, i) == 0)
		return (0);
	if (master->args.number_of_times_each_philosopher_must_eat
		!= master->philo[i].number_of_times_each_philosopher_ate)
	{
		if (sleepingphilo(master, i) == 0)
			return (0);
		if (thinkingphilo(master, i) == 0)
			return (0);
	}
	return (1);
}
