/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:34:24 by moturki           #+#    #+#             */
/*   Updated: 2023/12/09 19:34:25 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mutex_init(t_tab *info)
{
	int	i;

	i = 0;
	info->forks_mutex = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if (!info->forks_mutex)
		return (1);
	pthread_mutex_init(&info->print_mutex, NULL);
	pthread_mutex_init(&info->death_mutex, NULL);
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&info->forks_mutex[i], NULL);
		i++;
	}
	return (0);
}

int	philo_init(t_tab *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!info->philo)
		return (1);
	while (i < info->nb_philo)
	{
		info->philo[i].pos = i;
		info->philo[i].l_fork = i;
		info->philo[i].r_fork = (i + 1) % info->nb_philo;
		info->philo[i].miam_eated = 0;
		info->philo[i].last_miam = 0;
		info->philo[i].instance = info;
		i++;
	}
	return (0);
}

int	args_init(char **av, t_tab *info)
{
	info->nb_philo = ft_atoi(av[1]);
	info->ttdie = ft_atoi(av[2]);
	info->tteat = ft_atoi(av[3]);
	info->ttsleep = ft_atoi(av[4]);
	info->stop = 0;
	if (av[5])
		info->nb_eat = ft_atoi(av[5]);
	else
		info->nb_eat = -1;
	if (info->nb_eat <= 0 && av[5])
		return (1);
	if (info->nb_philo > 250 || info->nb_philo < 2 || info->ttdie < 0
		|| info->tteat < 0 || info->ttsleep < 0)
		return (1);
	return (0);
}
