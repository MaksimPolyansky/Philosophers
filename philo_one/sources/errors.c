/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 05:13:24 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/18 07:29:13 by heusebio         ###   ########.fr       */
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
		if ((*phils)[0]->print_mutex)
			free((*phils)[0]->print_mutex);
		if ((*phils)[0]->die)
			free((*phils)[0]->die);
		if ((*phils)[0]->eat)
			free((*phils)[0]->eat);
		while (--i)
		{
			if ((*phils)[i]->lfork)
				free((*phils)[i]->lfork);
			if ((*phils)[i])
				free((*phils)[i]);
		}
		free(*phils);
	}
	write(2, line, ft_strlen(line));
	write(2, "\n", 1);
	return (NULL);
}
