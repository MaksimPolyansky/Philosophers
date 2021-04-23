/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:29:15 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/22 20:10:38 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	my_zero(t_phils **phil, int ac, char **av)
{
	*(phil) = (t_phils *)malloc(sizeof(t_phils));
	if (*(phil) == NULL)
		return (0);
	(*phil)->num_of_phil = ft_atoi(av[1]);
	(*phil)->time_to_die = (size_t)ft_atoi(av[2]);
	(*phil)->time_to_eat = ft_atoi(av[3]);
	(*phil)->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*phil)->num_eat = ft_atoi(av[5]);
	else
		(*phil)->num_eat = -1;
	(*phil)->count_eat = 0;
	(*phil)->die = 0;
	(*phil)->print_sem = NULL;
	(*phil)->forks = NULL;
	return (1);
}

int	parse(t_phils ***phils, int ac, char **av)
{
	int		i;

	if (ac == 5 || ac == 6)
	{
		if (ft_atoi(av[1]) < 2 || ft_atoi(av[1]) > 200 || \
		ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || \
		ft_atoi(av[4]) < 60 || (ac == 6 && ft_atoi(av[5]) < 0))
			return (error_arg("Bad arguments!"));
		(*phils) = (t_phils **)malloc(sizeof(t_phils *) * ft_atoi(av[1]));
		if ((*phils) == NULL)
			return (error_arg("Bad malloc!"));
		i = -1;
		while (++i < ft_atoi(av[1]))
		{
			if (!my_zero(&(*phils)[i], ac, av))
				return (my_errors(&(*phils), "Bad malloc!"));
			(*phils)[i]->pos = i;
		}
	}
	else
		return (error_arg("Bad arguments!"));
	return (1);
}
