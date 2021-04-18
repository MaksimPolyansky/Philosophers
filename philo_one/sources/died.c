/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:19:21 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/18 04:57:44 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	*died(void *data)
{
	t_phils		*phil;
	size_t		time;

	phil = (t_phils *)data;
	pthread_create(&phil->thread, NULL, run, phil);
	while (1)
	{
		usleep(100);
		time = my_time() - phil->start_t;
		if ((time - phil->end_eat) > phil->time_to_die)
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
