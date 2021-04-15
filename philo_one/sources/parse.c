/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:21:52 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/15 23:22:37 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	my_zero(t_phils **phil, int ac, char **av)
{
	*(phil) = (t_phils*)malloc(sizeof(t_phils));
	if (*(phil) == NULL)
		exit(EXIT_FAILURE);
	(*phil)->num_of_phil = ft_atoi(av[1]);
	(*phil)->time_to_die = (__uint64_t)ft_atoi(av[2]);
	(*phil)->time_to_eat = ft_atoi(av[3]);
	(*phil)->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*phil)->num_eat = ft_atoi(av[5]);
	else
		(*phil)->num_eat = 0;
	(*phil)->count_eat = 0;
	(*phil)->lfork = NULL;
	(*phil)->rfork = NULL;
}

t_phils	**parse(int ac, char **av)
{
	t_phils	**phils;
	int		i;

	if (ac == 5 || ac == 6)
	{
		if (ft_atoi(av[1]) < 2 || ft_atoi(av[1]) > 200 || \
		ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || \
		ft_atoi(av[4]) < 60 || (ac == 6 && ft_atoi(av[5]) < 0))
			exit(EXIT_FAILURE);
		phils = (t_phils**)malloc(sizeof(t_phils*) * ft_atoi(av[1]));
		if (phils == NULL)
			exit(EXIT_FAILURE);
		i = -1;
		while (++i < ft_atoi(av[1]))
		{
			my_zero(&phils[i], ac, av);
			phils[i]->pos = i;
		}
	}
	else
		exit(EXIT_FAILURE);
	return (phils);
}
