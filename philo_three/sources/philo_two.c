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

#include "../includes/philo_three.h"

void	*count_eat(void *data)
{
	t_phils		*phil;
	int			cout;

	phil = (t_phils*)data;
	cout = 0;
	while (phil->num_of_phil != cout)
	{
		sem_wait(phil->eats);
		cout++;
	}
	*phil->eat = 1;
	return (NULL);
}

void	*died_phil(void *data)
{
	t_phils		*phil;

	phil = (t_phils*)data;
	sem_wait(phil->dieds);
	*phil->die = 1;
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
	int		stat;
	// int		res;
	__uint64_t	start;

	phils = parse(ac, av);
	phils[0]->print_sem = sem_open("Phils", O_CREAT, 0600, 1);
	sem_unlink("Phils");
	phils[0]->forks = sem_open("Forks", O_CREAT, 0600, phils[0]->num_of_phil);
	sem_unlink("Forks");
	phils[0]->eats = sem_open("Eets", O_CREAT, 0600, 0);
	sem_unlink("Eats");
	phils[0]->dieds = sem_open("Deads", O_CREAT, 0600, 0);
	sem_unlink("Deads");
	i = 0;
	while (++i < phils[0]->num_of_phil)
	{
		phils[i]->print_sem = phils[0]->print_sem;
		phils[i]->forks = phils[0]->forks;
		phils[i]->eats = phils[0]->eats;
		phils[i]->dieds = phils[0]->dieds;
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
	{
		phils[k]->fork_d = fork();
		if (phils[k]->fork_d == 0)
		{
			died(phils[k]);
		}
	}
	// while (++z < phils[0]->num_of_phil)
	// {
	// 	pthread_join(phils[z]->thread_d, NULL);
	// }
	pthread_t	*t1;
	pthread_t	*t2;
	t1 = malloc(sizeof(pthread_t));
	t2 = malloc(sizeof(pthread_t));
	if (phils[0]->num_eat != 0)
		pthread_create(t1, NULL, count_eat, phils[0]);
	pthread_create(t2, NULL, died_phil, phils[0]);
	while (!waitpid(0, &stat, WNOHANG))
	{
		if (*phils[0]->eat || *phils[0]->die)
			break;
	}
	// res = WEXITSTATUS(stat);
	z = -1;
	while (++z < phils[0]->num_of_phil)
		kill(phils[z]->fork_d, SIGKILL);
	sem_close(phils[0]->print_sem);
	sem_close(phils[0]->forks);
	sem_close(phils[0]->dieds);
	sem_close(phils[0]->eats);
	return (EXIT_SUCCESS);
}
