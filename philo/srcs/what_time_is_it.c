/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_time_is_it.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <lkhamlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:26:12 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/02/16 16:41:51 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//tv sec en sec donc * 1000 dc 1sec = 1000ms
//et usec, micro second dc 1 micro = 0.001 ms

long long	current_time(long long time)
{
	if (time > 0)
	{
		return (what_time_is_it() - time);
	}
	return (0);
}

long long	what_time_is_it(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

void	actions_time(long long time)
{
	usleep(time * 1000);
}
