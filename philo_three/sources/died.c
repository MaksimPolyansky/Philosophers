/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:30:28 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/16 22:30:26 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int		died(t_phils *phil)
{
	__uint64_t	time;

	pthread_create(&phil->thread, NULL, run, phil);
	usleep(2000);
	while (1)
	{
		time = my_time() - phil->start_t;
		if ((time - phil->end_eat) > phil->time_to_die)
		{
			print_info(phil, "died");
			sem_post(phil->dieds);
			// pthread_detach(phil->thread);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
