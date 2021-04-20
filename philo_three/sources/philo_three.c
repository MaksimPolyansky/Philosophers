/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 09:08:58 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/20 21:41:52 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	my_free(t_phils ***phils)
{
	int	i;

	i = (*phils)[0]->num_of_phil;
	if (*phils)
	{
		sem_close((*phils)[0]->print_sem);
		sem_close((*phils)[0]->forks);
		if ((*phils)[0]->die)
			free((*phils)[0]->die);
		if ((*phils)[0]->eat)
			free((*phils)[0]->eat);
		while (--i)
		{
			if ((*phils)[i])
				free((*phils)[i]);
		}
		free(*phils);
	}
	exit(0);
}

void	to_eat(t_phils **phil)
{
	sem_wait((*phil)->forks);
	sem_wait((*phil)->forks);
	print_info((*phil), "has taken a forks");
	(*phil)->end_eat = my_time();
	print_info((*phil), "is eating");
	usleep((*phil)->time_to_eat * 1000);
	sem_post((*phil)->forks);
	sem_post((*phil)->forks);
	(*phil)->count_eat++;
}

void	*run(void *data)
{
	t_phils	*phil;

	phil = (t_phils *)data;
	phil->end_eat = my_time();
	if (phil->pos % 2)
		usleep(100);
	while (1)
	{
		print_info(phil, "is thinking");
		to_eat(&phil);
		print_info(phil, "is sleeping");
		usleep(phil->time_to_sleep * 1000);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_phils	**phils;
	t_all	all;

	if (!parse(&phils, ac, av))
		exit(1);
	all.phils = phils[0]->num_of_phil;
	if (!init_forks(&phils) || !init_print(&phils, &all))
		exit(1);
	my_free(&phils);
	return (EXIT_SUCCESS);
}
