/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 05:13:24 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/18 05:13:52 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	*error_arg(char *line)
{
	write(2, line, ft_strlen(line));
	write(2, "\n", 1);
	return (NULL);
}

void	*my_errors(t_phils ***phils, char *line)
{
	int	i;

	i = (*phils)[0]->num_of_phil;
	if (*phils)
	{
		while (--i)
		{
			if ((*phils)[i]->lfork)
				free((*phils)[i]->lfork);
			if ((*phils)[i]->rfork)
				free((*phils)[i]->rfork);
			if ((*phils)[i]->print_mutex)
				free((*phils)[i]->print_mutex);
			if ((*phils)[i]->die)
				free((*phils)[i]->die);
			if ((*phils)[i]->eat)
				free((*phils)[i]->eat);
		}
	}
	write(2, line, ft_strlen(line));
	write(2, "\n", 1);
	return (NULL);
}
