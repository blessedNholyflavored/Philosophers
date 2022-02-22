/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onlyonephilo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <lkhamlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:20:54 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/02/16 16:41:08 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_printone(t_master *master, int id, char *status)
{
	long long	now;

	master->deadphilosopher = 0;
	now = current_time(master->time);
	pthread_mutex_lock(&master->write);
	if (master->deadphilosopher == 1)
		return (0);
	if (master->deadphilosopher == 1)
	{
		pthread_mutex_unlock(&master->write);
		return (0);
	}
	else
		printf("%-10lld philosopher %d %s\n", now, id, status);
	pthread_mutex_unlock(&master->write);
	return (1);
}

int	onlyonephilo(t_master *master)
{
	if (pthread_mutex_init(&master->write, NULL) != 0)
		return (0);
	master->time = what_time_is_it();
	philo_printone(master, 1, FORK);
	actions_time(master->args.time_to_die);
	philo_printone(master, 1, DIE);
	ft_free(master);
	return (1);
}
/*

la routine :
 - si le nb de fois qui doit etre mange > 0
  on verifie que le nb_eat > nb_ate et que le philo est pas dead
	si c ok 
	on exxecute la routine
- sinon
	tant que philo pas mort
		on execute routine

la fonction pr executer 
- si ohilo_eat == 0
	return 
	si args.nb_eat != philo[i].nb_ate
		si philo_sleep == 0
			return 0
		si pphilo think == 0
		return 0
	return 1;


- fonction eat 
*/
