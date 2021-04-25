/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 08:48:47 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/25 08:05:32 by heusebio         ###   ########.fr       */
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

void	whihle_print(t_phils ***phils, t_all *all)
{
	int		p;

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
}

int	init_print(t_phils ***phils, t_all *all)
{
	size_t	start;
	int		p;

	p = -1;
	start = my_time();
	while (++p < (*phils)[0]->num_of_phil)
		(*phils)[p]->start_t = start;
	(*all).all_pid = malloc(sizeof(pid_t) * (*all).phils + 1);
	if (!(*all).all_pid)
		return ((int)my_errors(&(*phils), \
			"Bad malloc print!") + my_error_all(&(*all)));
	whihle_print(&(*phils), &(*all));
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
		if ((int)count == (*phils)[0]->num_of_phil)
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
	if (pthread_create(&(*phils)->thread_d, NULL, died, (*phils)))
		exit(21);
	while (1)
	{
		run((*phils));
		if ((*phils)->count_eat == (*phils)->num_eat)
			exit(42);
	}
	exit(0);
}
