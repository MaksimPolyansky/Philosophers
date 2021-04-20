/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 08:48:47 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/20 21:37:19 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	init_forks(t_phils ***phils)
{
	int		i;

	sem_unlink("Print");
	sem_unlink("Eat");
	(*phils)[0]->print_sem = sem_open("Print", O_CREAT, 0600, 1);
	(*phils)[0]->forks = sem_open("Eat", O_CREAT, 0600, \
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

int	init_print(t_phils ***phils, t_all *all)
{
	// int		*d;
	// int		*w;
	size_t	start;
	int		p;

	// d = (int *)malloc(sizeof(int));
	// w = (int *)malloc(sizeof(int));
	// if (d == 0 || w == 0)
	// 	return ((int)my_errors(&(*phils), "Bad malloc print!"));
	// *d = 0;
	// *w = 0;
	p = -1;
	start = my_time();
	while (++p < (*phils)[0]->num_of_phil)
	{
		// (*phils)[p]->die = d;
		// (*phils)[p]->eat = w;
		(*phils)[p]->start_t = start;
	}
	p = -1;
	while (++p < (int)all->phils)
	{
		all->all_pid[p] = fork();
		if (all->all_pid[p] == 0)
		{
			to_go(&(*phils)[p]);
			exit(0);
		}
		else if (all->all_pid[p] < 0)
		{
			while (all->all_pid[p] && 0 <= p)
				kill(all->all_pid[p--], SIGKILL);
			exit(21);
		}
	}
	to_end(&(*phils), &(*all));
	return (1);
}

void	to_end(t_phils ***phils, t_all *all)
{
	int		stat;
	size_t	count;

	count = 0;
	while (1)
	{
		waitpid(-1, &stat, 0);
		stat = WEXITSTATUS(stat);
		if ((*phils)[0]->num_eat != -1 && stat == 42)
			count++;
		else
		{
			while (all->all_pid[count] && count < all->phils)
				kill(all->all_pid[count++], SIGKILL);
			exit(21);
		}
		if ((int)count == (*phils)[0]->num_eat)
		{
			count = 0;
			while (all->all_pid[count] && count < all->phils)
				kill(all->all_pid[count++], SIGKILL);
			exit(0);
		}
	}
}

void	to_go(t_phils **phils)
{
	// int		z;

	if (pthread_create(&(*phils)->thread_d, NULL, died, (*phils)))
		exit(21);
	while (1)
	{
		if ((*phils)->count_eat == (*phils)->num_eat && (*phils)->num_eat != -1)
			exit(42);
	}


	// z = -1;
	// while (++z < (*phils)->num_of_phil)
	// {
	// 	if (pthread_join((*phils)->thread_d, NULL))
	// 		return ((int)my_errors(&(*phils), "Bad pthread join!"));
	// }
	// z = -1;
	// while (++z < (*phils)[0]->num_of_phil)
	// {
	// 	if (sem_post((*phils)[0]->forks) || sem_post(((*phils)[0]->print_sem)))
	// 		return ((int)my_errors(&(*phils), "Bad sem post!"));
	// }
	exit(0);
}
