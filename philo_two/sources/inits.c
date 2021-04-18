/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 08:48:47 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/18 09:12:19 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int	init_forks(t_phils ***phils)
{
	int		i;

	sem_unlink("Phils");
	sem_unlink("Forks");
	(*phils)[0]->print_sem = sem_open("Phils", O_CREAT, 0600, 1);
	(*phils)[0]->forks = sem_open("Forks", O_CREAT, 0600, \
		(*phils)[0]->num_of_phil);
	if ((*phils)[0]->print_sem == SEM_FAILED || \
		(*phils)[0]->forks == SEM_FAILED)
		return ((int)my_errors(&(*phils), "Bad sem open!"));
	i = 0;
	while (++i < (*phils)[0]->num_of_phil)
	{
		(*phils)[i]->print_sem = (*phils)[0]->print_sem;
		(*phils)[i]->forks = (*phils)[0]->forks;
	}
	return (1);
}

int	init_print(t_phils ***phils)
{
	int		*d;
	int		*w;
	size_t	start;
	int		p;

	d = (int *)malloc(sizeof(int));
	w = (int *)malloc(sizeof(int));
	if (d == 0 || w == 0)
		return ((int)my_errors(&(*phils), "Bad malloc print!"));
	*d = 0;
	*w = 0;
	p = -1;
	start = my_time();
	while (++p < (*phils)[0]->num_of_phil)
	{
		(*phils)[p]->die = d;
		(*phils)[p]->eat = w;
		(*phils)[p]->start_t = start;
	}
	return (1);
}

int	to_go(t_phils ***phils)
{
	int		k;
	int		z;

	k = -1;
	while (++k < (*phils)[0]->num_of_phil)
	{
		if (pthread_create(&(*phils)[k]->thread_d, NULL, died, (*phils)[k]))
			return ((int)my_errors(&(*phils), "Bad pthread create!"));
	}
	z = -1;
	while (++z < (*phils)[0]->num_of_phil)
	{
		if (pthread_join((*phils)[z]->thread_d, NULL))
			return ((int)my_errors(&(*phils), "Bad pthread join!"));
	}
	z = -1;
	while (++z < (*phils)[0]->num_of_phil)
	{
		if (sem_post((*phils)[0]->forks) || sem_post(((*phils)[0]->print_sem)))
			return ((int)my_errors(&(*phils), "Bad sem post!"));
	}
	return (1);
}
