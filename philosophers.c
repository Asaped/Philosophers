/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:34:53 by moturki           #+#    #+#             */
/*   Updated: 2023/12/09 19:40:14 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_info(t_tab *info)
{
	free(info->philo);
	free(info->forks_mutex);
}

void	stop(t_tab *info, pthread_t *tid)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
		pthread_join(tid[i], NULL);
	pthread_join(tid[info->nb_philo], NULL);
	free(tid);
	i = -1;
	while (++i < info->nb_philo)
		pthread_mutex_destroy(&(info->forks_mutex[i]));
	pthread_mutex_destroy(&(info->print_mutex));
	pthread_mutex_destroy(&(info->death_mutex));
	free_info(info);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->instance->forks_mutex[philo->l_fork]);
	ft_msg(philo, timestamp() - philo->instance->first_ts, 1);
	pthread_mutex_lock(&philo->instance->forks_mutex[philo->r_fork]);
	ft_msg(philo, timestamp() - philo->instance->first_ts, 1);
	pthread_mutex_lock(&philo->instance->death_mutex);
	philo->last_miam = timestamp();
	ft_msg(philo, timestamp() - philo->instance->first_ts, 3);
	pthread_mutex_unlock(&philo->instance->death_mutex);
	ft_usleep(philo->instance->tteat);
	philo->miam_eated += 1;
	pthread_mutex_unlock(&philo->instance->forks_mutex[philo->l_fork]);
	pthread_mutex_unlock(&philo->instance->forks_mutex[philo->r_fork]);
	if (philo->miam_eated == philo->instance->nb_eat
		&& philo->instance->nb_eat != -1)
	{
		ft_msg(philo, timestamp() - philo->instance->first_ts, 6);
		return (1);
	}
	ft_msg(philo, timestamp() - philo->instance->first_ts, 4);
	ft_usleep(philo->instance->ttsleep);
	ft_msg(philo, timestamp() - philo->instance->first_ts, 5);
	return (0);
}

void	*death_check(void *info)
{
	t_tab	*tab;
	int		i;

	i = -1;
	tab = info;
	while (++i < tab->nb_philo)
	{
		if (timestamp() - tab->philo[i].last_miam >= tab->ttdie
			&& tab->philo->miam_eated != tab->nb_eat)
		{
			ft_msg(&tab->philo[i], timestamp() - tab->first_ts, 2);
			tab->stop = 1;
			return (0);
		}
		if (tab->philo->miam_eated == tab->nb_eat)
			return (0);
		if (i == tab->nb_philo - 1)
			i = -1;
	}
	return (0);
}

int	start(t_tab *info)
{
	pthread_t	*tid;	
	int			i;

	i = 0;
	tid = malloc(sizeof(pthread_t) * (info->nb_philo + 1));
	if (!tid)
		return (1);
	info->first_ts = timestamp();
	while (i < info->nb_philo)
	{
		if (pthread_create(&tid[i], NULL, &routine, &info->philo[i]))
			return (1);
		i++;
	}
	if (pthread_create(&tid[info->nb_philo], NULL, &death_check, info))
		return (1);
	stop(info, tid);
	return (0);
}
