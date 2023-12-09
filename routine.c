/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:35:08 by moturki           #+#    #+#             */
/*   Updated: 2023/12/09 19:35:35 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *philo2)
{
	t_philo	*philo;

	philo = (t_philo *)philo2;
	philo->last_miam = timestamp();
	if (philo->pos % 2)
		usleep(15000);
	while (philo->instance->stop == 0
		&& philo->last_miam != philo->instance->nb_eat)
	{
		if (eat(philo))
			break ;
	}
	return (NULL);
}
