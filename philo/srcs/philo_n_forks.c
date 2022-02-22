/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_n_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <lkhamlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:21:55 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/02/16 16:39:30 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fillphilo(t_master *master, int i, int j)
{
	master->philo[i].id = i + 1;
	master->philo[i].number_of_times_each_philosopher_ate = 0;
	master->philo[i].time_to_die = 0;
	master->philo[i].fork.left = i;
	master->philo[i].fork.right = j;
}

int	add_philo(t_master *master)
{
	int	i;
	int	j;

	master->philo = malloc(sizeof(t_philo) * (master->args.compteurphilo + 1));
	if (master->philo == NULL)
		return (0);
	i = 0;
	j = 1;
	while (j < master->args.compteurphilo)
	{
		fillphilo(master, i, j);
		i++;
		j++;
	}
	j = 0;
	fillphilo(master, i, j);
	return (1);
}

int	add_forks(t_master *master)
{
	int	i;

	master->forks = malloc(sizeof(pthread_mutex_t)
			* master->args.compteurphilo + 1);
	if (master->forks == NULL)
		return (0);
	i = 0;
	while (i < master->args.compteurphilo)
	{
		if (pthread_mutex_init(&master->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
