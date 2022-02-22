/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <lkhamlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:07:10 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/02/16 16:39:16 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	checktime(t_master *master, int *i)
{
	int	time ;

	pthread_mutex_lock(&master->timemutex);
	time = current_time(master->philo[*i].time_to_die);
	pthread_mutex_unlock(&master->timemutex);
	pthread_mutex_lock(&master->timemutex);
	if (time > master->args.time_to_die)
	{
		pthread_mutex_unlock(&master->timemutex);
		return (0);
	}
	pthread_mutex_unlock(&master->timemutex);
	return (1);
}

int	dyingphilo(t_master *master, int *i)
{
	if (*i == master->args.compteurphilo)
		*i = 0;
	if (checktime(master, i) == 0)
	{
		philo_print(master, master->philo[*i].id, DIE);
		pthread_mutex_lock(&master->dead);
		master->deadphilosopher = 1;
		pthread_mutex_unlock(&master->dead);
		return (1);
	}
	i++;
	return (0);
}

void	*checker(void *args)
{
	t_master	*master;
	int			i;

	master = (t_master *)args;
	i = 0;
	if (master->args.number_of_times_each_philosopher_must_eat > 0)
	{
		while ((check_ate(master, i) == -1) && (checkdead(master) == 0))
		{
			if (dyingphilo(master, &i) == 1)
				break ;
		}
	}
	else
	{	
		while (master->deadphilosopher == 0)
		{
			if (dyingphilo(master, &i) == 1)
				break ;
		}
	}
	return (NULL);
}
