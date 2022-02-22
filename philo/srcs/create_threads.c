/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <lkhamlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:11:29 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/02/16 16:37:27 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create(t_master *master)
{
	if (pthread_mutex_init(&master->write, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&master->dead, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&master->nbmutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&master->already_ate, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&master->timemutex, NULL) != 0)
		return (0);
	return (1);
}

int	init_thread(t_master *master)
{
	int	i;

	i = 0;
	master->deadphilosopher = 0;
	master->time = what_time_is_it();
	if (create(master) == 0)
		return (0);
	while (i < master->args.compteurphilo)
	{
		pthread_mutex_lock(&master->nbmutex);
		master->nb_thread = i;
		pthread_mutex_unlock(&master->nbmutex);
		if (pthread_create(&master->philo[i].thread, NULL,
				&routine, (void *) master) != 0)
			return (0);
		i++;
		usleep(1000);
	}
	if (pthread_create(&master->thread2, NULL,
			&checker, (void *) master) != 0)
		return (0);
	usleep(1000);
	if (join_threads(master) == 0)
		return (0);
	return (1);
}

int	join_threads(t_master *master)
{
	int	i;

	i = 0;
	while (i < master->args.compteurphilo)
	{
		if (pthread_join(master->philo[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(master->thread2, NULL) != 0)
		return (0);
	return (1);
}

int	destroy_threads(t_master *master)
{
	int	i;

	i = 0;
	while (i < master->args.compteurphilo)
	{
		pthread_mutex_destroy(&master->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&master->nbmutex);
	pthread_mutex_destroy(&master->dead);
	pthread_mutex_destroy(&master->already_ate);
	pthread_mutex_destroy(&master->write);
	return (1);
}
