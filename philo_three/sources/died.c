/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:30:28 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/20 21:43:28 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*died(void *data)
{
	t_phils		*phil;

	phil = (t_phils *)data;
	pthread_create(&phil->thread, NULL, run, phil);
	while (1)
	{
		usleep(100);
		if ((my_time() - phil->end_eat) > phil->time_to_die * 1000)
		{
			print_info(phil, "died");
			*phil->die = 1;
			pthread_detach(phil->thread);
			return (NULL);
		}
		if (*phil->die || *phil->eat == phil->num_of_phil)
		{
			pthread_detach(phil->thread);
			return (NULL);
		}
	}
	return (NULL);
}
