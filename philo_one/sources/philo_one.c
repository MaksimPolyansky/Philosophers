/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 06:47:34 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/18 07:30:51 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	my_free(t_phils ***phils)
{
	int	i;

	i = (*phils)[0]->num_of_phil;
	if (*phils)
	{
		if ((*phils)[0]->print_mutex)
			free((*phils)[0]->print_mutex);
		if ((*phils)[0]->die)
			free((*phils)[0]->die);
		if ((*phils)[0]->eat)
			free((*phils)[0]->eat);
		while (--i)
		{
			if ((*phils)[i]->lfork)
				free((*phils)[i]->lfork);
			if ((*phils)[i])
				free((*phils)[i]);
		}
		free(*phils);
	}
}

void	to_eat(t_phils **phil)
{
	pthread_mutex_lock(&(*phil)->lfork->mutex_f);
	pthread_mutex_lock(&(*phil)->rfork->mutex_f);
	print_info((*phil), "has taken a forks");
	(*phil)->lfork->fork = 0;
	(*phil)->rfork->fork = 0;
	(*phil)->end_eat = my_time() - (*phil)->start_t;
	print_info((*phil), "is eating");
	usleep((*phil)->time_to_eat * 1000);
	(*phil)->lfork->fork = 1;
	(*phil)->rfork->fork = 1;
	pthread_mutex_unlock(&(*phil)->lfork->mutex_f);
	pthread_mutex_unlock(&(*phil)->rfork->mutex_f);
}

void	*run(void *data)
{
	t_phils	*phil;

	phil = (t_phils *)data;
	phil->end_eat = my_time() - phil->start_t;
	if (phil->pos % 2)
		usleep(100);
	while (1)
	{
		print_info(phil, "is thinking");
		to_eat(&phil);
		phil->count_eat++;
		if (phil->count_eat == phil->num_eat)
			(*phil->eat)++;
		print_info(phil, "is sleeping");
		usleep(phil->time_to_sleep * 1000);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_phils	**phils;

	if (!parse(&phils, ac, av) || !init_forks(&phils) || !init_print(&phils) \
		|| !to_go(&phils))
		return (1);
	my_free(&phils);
	return (EXIT_SUCCESS);
}
