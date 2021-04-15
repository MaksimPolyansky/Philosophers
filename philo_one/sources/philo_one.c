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

#include "../includes/philo_one.h"

void	print_info(t_phils *phil, char *line)
{
	pthread_mutex_lock(phil->print_mutex);
	if (*phil->die == 1)
	{
		pthread_mutex_unlock(phil->print_mutex);
		return ;
	}
	printf("%lu %d %s\n", my_time() - phil->start_t, phil->pos + 1, line);
	pthread_mutex_unlock(phil->print_mutex);
}

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
		pthread_mutex_lock(&phil->lfork->mutex_f);
		pthread_mutex_lock(&phil->rfork->mutex_f);
		print_info(phil, "has taken a forks");
		phil->lfork->fork = 0;
		phil->rfork->fork = 0;
		phil->end_eat = my_time() - phil->start_t;
		print_info(phil, "is eating");
		usleep(phil->time_to_eat * 1000);
		phil->lfork->fork = 1;
		phil->rfork->fork = 1;
		pthread_mutex_unlock(&phil->lfork->mutex_f);
		pthread_mutex_unlock(&phil->rfork->mutex_f);
		phil->count_eat++;
		if (phil->count_eat == phil->num_eat)
			(*phil->eat)++;
		print_info(phil, "is sleeping");
		usleep(phil->time_to_sleep * 1000);
	}
	return (NULL);
}

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
	i = 0;
	phils[i]->lfork = (t_fork*)malloc(sizeof(t_fork));
	if (phils[i]->lfork == NULL)
		exit(EXIT_FAILURE);
	phils[i]->lfork->fork = 1;
	pthread_mutex_init(&phils[i]->lfork->mutex_f, NULL);
	i = -1;
	while (++i < phils[0]->num_of_phil - 1)
	{
		phils[i]->rfork = (t_fork*)malloc(sizeof(t_fork));
		if (phils[i]->rfork == NULL)
			exit(EXIT_FAILURE);
		phils[i]->rfork->fork = 1;
		pthread_mutex_init(&phils[i]->rfork->mutex_f, NULL);
		phils[i + 1]->lfork = phils[i]->rfork;
	}
	phils[i]->rfork = phils[0]->lfork;

	d = (int*)malloc(sizeof(int));
	w = (int*)malloc(sizeof(int));
	if (d == 0 || w == 0)
		exit(EXIT_FAILURE);
	*d = 0;
	*w = 0;
	pthread_mutex_t		*mutex_t;
	mutex_t = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex_t, NULL);
	p = -1;
	start = my_time();
	while (++p < phils[0]->num_of_phil)
	{
		phils[p]->die = d;
		phils[p]->eat = w;
		phils[p]->print_mutex = mutex_t;
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
	return (EXIT_SUCCESS);
}
