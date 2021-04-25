/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:30:28 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/25 05:05:34 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*died(void *data)
{
	t_phils		*phil;

	phil = (t_phils *)data;
	while (1)
	{
		usleep(50);
		if ((my_time() - phil->end_eat) > phil->time_to_die)
		{
			phil->die = 1;
			print_info(phil, "died");
			pthread_detach(phil->thread_d);
			exit(21);
		}
	}
	return (NULL);
}
