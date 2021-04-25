/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 06:43:56 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/25 04:57:56 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	init_mutex(t_phils ***phils, t_fork **fork_s)
{
	pthread_mutex_t	forks;

	(*fork_s) = (t_fork *)malloc(sizeof(t_fork));
	if ((*fork_s) == NULL)
		return (my_errors(&(*phils), "Bad malloc mutex!"));
	if (pthread_mutex_init(&forks, NULL))
		return (my_errors(&(*phils), "Bad pthread init mutex!"));
	(*fork_s)->mutex_f = forks;
	(*fork_s)->fork = 1;
	return (1);
}

int	init_forks(t_phils ***phils)
{
	int		i;

	if (!init_mutex(&(*phils), &(*phils)[0]->lfork))
		return (0);
	i = -1;
	while (++i < (*phils)[0]->num_of_phil - 1)
	{
		if (!init_mutex(&(*phils), &(*phils)[i]->rfork))
			return (0);
		(*phils)[i + 1]->lfork = (*phils)[i]->rfork;
	}
	(*phils)[i]->rfork = (*phils)[0]->lfork;
	return (1);
}

int	init_print(t_phils ***phils)
{
	int					*d;
	int					*w;
	int					p;
	size_t				start;
	pthread_mutex_t		*mutex_t;

	d = (int *)malloc(sizeof(int));
	w = (int *)malloc(sizeof(int));
	mutex_t = malloc(sizeof(pthread_mutex_t));
	if (d == 0 || w == 0 || mutex_t == NULL)
		return (my_errors(&(*phils), "Bad malloc print!"));
	*d = 0;
	*w = 0;
	if (pthread_mutex_init(mutex_t, NULL))
		return (my_errors(&(*phils), "Bad pthread init print!"));
	p = -1;
	start = my_time();
	while (++p < (*phils)[0]->num_of_phil)
	{
		(*phils)[p]->die = d;
		(*phils)[p]->eat = w;
		(*phils)[p]->print_mutex = mutex_t;
		(*phils)[p]->start_t = start;
	}
	return (1);
}

void	*check_status(t_phils ***phils)
{
	int	i;

	i = 0;
	while ((g_total_eat / (*phils)[0]->num_of_phil < (*phils)[0]->num_eat \
		|| (*phils)[0]->num_eat == -1) && !g_die)
	{
		if (i == (*phils)[0]->num_of_phil - 1)
			i = 0;
		died((*phils)[i]);
		i++;
		upgrade_usleep(0.1);
	}
	return (NULL);
}

int	to_go(t_phils ***phils)
{
	int	i;

	i = 0;
	while (i < (*phils)[0]->num_of_phil)
	{
		pthread_create(&(*phils)[i]->thread, NULL, run, (*phils)[i]);
		i++;
	}
	check_status(&(*phils));
	i = 0;
	while (i < (*phils)[0]->num_of_phil)
	{
		if (pthread_detach((*phils)[i++]->thread))
			return (my_errors(&(*phils), "Bad pthread join!"));
	}
	return (1);
}
