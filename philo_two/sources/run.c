/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:31:59 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/15 23:32:22 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

void	*run(void *data)
{
	t_phils	*phil;

	phil = (t_phils*)data;
	phil->end_eat = my_time() - phil->start_t;
	if (phil->pos % 2)
		usleep(1000);
	while (1)
	{
		print_info(phil, "is thinking");
		sem_wait(phil->forks);
		sem_wait(phil->forks);
		print_info(phil, "has taken a forks");
		phil->end_eat = my_time() - phil->start_t;
		print_info(phil, "is eating");
		usleep(phil->time_to_eat * 1000);
		sem_post(phil->forks);
		sem_post(phil->forks);
		phil->count_eat++;
		if (phil->count_eat == phil->num_eat)
			(*phil->eat)++;
		print_info(phil, "is sleeping");
		usleep(phil->time_to_sleep * 1000);
	}
	return (NULL);
}
