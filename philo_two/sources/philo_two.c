/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philso_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:52:06 by heusebio          #+#    #+#             */
/*   Updated: 2021/02/14 14:28:48 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

int		main(int ac, char **av)
{
	t_phils	**phils;
	int		i;
	int		p;
	int		k;
	int		z;
	int		*d;
	int		*w;
	__uint64_t	start;

	phils = parse(ac, av);
	phils[0]->print_sem = sem_open("Phils", O_CREAT, 0600, 1);
	sem_unlink("Phils");
	phils[0]->forks = sem_open("Forks", O_CREAT, 0600, phils[0]->num_of_phil);
	sem_unlink("Forks");
	i = 0;
	while (++i < phils[0]->num_of_phil)
	{
		phils[i]->print_sem = phils[0]->print_sem;
		phils[i]->forks = phils[0]->forks;
	}
	d = (int*)malloc(sizeof(int));
	w = (int*)malloc(sizeof(int));
	if (d == 0 || w == 0)
		exit(EXIT_FAILURE);
	*d = 0;
	*w = 0;
	p = -1;
	start = my_time();
	while (++p < phils[0]->num_of_phil)
	{
		phils[p]->die = d;
		phils[p]->eat = w;
		phils[p]->start_t = start;
	}
	k = -1;
	while (++k < phils[0]->num_of_phil)
		pthread_create(&phils[k]->thread_d, NULL, died, phils[k]);

	z = -1;
	while (++z < phils[0]->num_of_phil)
	{
		pthread_join(phils[z]->thread_d, NULL);
	}
	sem_close(phils[0]->print_sem);
	sem_close(phils[0]->forks);
	return (EXIT_SUCCESS);
}
