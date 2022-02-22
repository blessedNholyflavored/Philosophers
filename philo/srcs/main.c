/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <lkhamlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:16:20 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/02/07 16:37:13 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_args(int ac, char **av, t_master *master)
{
	if (ac == 5 || ac == 6)
	{
		master->args.compteurphilo = ft_atoi(av[1]);
		master->args.time_to_die = ft_atoi(av[2]);
		master->args.time_to_eat = ft_atoi(av[3]);
		master->args.time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			master->args.number_of_times_each_philosopher_must_eat
				= ft_atoi(av[5]);
		else
			master->args.number_of_times_each_philosopher_must_eat = -1;
		return (1);
	}
	return (0);
}

void	args_error_messages(t_master *master, int ac)
{
	if (!master->args.compteurphilo)
		printf("wrong number of philosophers\n");
	if (!master->args.time_to_die)
		printf("wrong input for time to die\n");
	if (!master->args.time_to_sleep)
		printf("wrong input for time to sleep\n");
	if (!master->args.time_to_eat)
		printf("wrong input for time to eat\n");
	if (ac == 6 && !master->args.number_of_times_each_philosopher_must_eat)
		printf("wrong input for number of times philo should eat\n");
}

int	argumentschecker(int ac, char **av, t_master *master)
{
	if (ac <= 4)
	{
		printf("Error arguments amount: check the subject\n");
		return (0);
	}
	else if (get_args(ac, av, master) == 0)
	{
		printf("Error arguments: shoukd be between 4 and 5\n");
		return (0);
	}
	else
	{
		args_error_messages(master, ac);
		if (!master->args.compteurphilo || !master->args.time_to_sleep
			|| !master->args.time_to_die || !master->args.time_to_eat
			|| (ac == 6
				&& !master->args.number_of_times_each_philosopher_must_eat))
			return (0);
	}
	return (1);
}

void	ft_free(t_master *master)
{
	free(master->philo);
	free(master->forks);
}

int	main(int ac, char **av)
{
	t_master	master;

	if (argumentschecker(ac, av, &master) == 0)
		return (1);
	if (add_philo(&master) == 0)
		return (1);
	if (add_forks(&master) == 0)
		return (1);
	if (master.args.compteurphilo == 1)
	{
		if (onlyonephilo(&master) == 0)
			return (1);
		return (0);
	}
	if (init_thread(&master) == 0)
		return (1);
	if (destroy_threads(&master) == 0)
		return (1);
	ft_free(&master);
	return (0);
}
