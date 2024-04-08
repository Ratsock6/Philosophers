/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:43:54 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/01 17:17:30 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo, t_states states)
{
	long	t;

	pthread_mutex_lock(&philo->core->arg.write);
	t = get_time(philo->core);
	if (!ft_is_finish(philo))
	{
		if (states == FORK)
			printf("\e[92m%5li Philosophers %9s[%3li] has taken a fork.\e[0m\n",
				t, philo->name, philo->id);
		else if (states == EAT)
			printf("\e[32m%5li Philosophers %9s[%3li] is eating.\e[0m\n",
				t, philo->name, philo->id);
		else if (states == SLEEP)
			printf("\e[94m%5li Philosophers %9s[%3li] is sleeping.\e[0m\n",
				t, philo->name, philo->id);
		else if (states == THINK)
			printf("\e[33m%5li Philosophers %9s[%3li] is thinking.\e[0m\n",
				t, philo->name, philo->id);
		else if (states == DEAD)
			printf("\e[31m%5li Philosophers %9s[%3li] died.\e[0m\n",
				t, philo->name, philo->id);
	}
	pthread_mutex_unlock(&philo->core->arg.write);
}

static bool	ft_one_philo(t_philo *philo)
{
	bool	is_finish;

	pthread_mutex_lock(&philo->core->arg.m_check);
	is_finish = philo->core->arg.finish;
	pthread_mutex_unlock(&philo->core->arg.m_check);
	return (is_finish);
}

void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_f);
	philo_print(philo, FORK);
	pthread_mutex_lock(&philo->core->arg.m_check);
	if (philo->core->arg.n_philo == 1)
	{
		pthread_mutex_unlock(&philo->core->arg.m_check);
		pthread_mutex_unlock(&philo->left_f);
		while (!ft_one_philo(philo))
			usleep(10);
		return ;
	}
	pthread_mutex_unlock(&philo->core->arg.m_check);
	pthread_mutex_lock(philo->right_f);
	philo_print(philo, FORK);
}

void	ft_eating(t_philo *philo)
{
	size_t	time;

	time = 0;
	philo_print(philo, EAT);
	if (!ft_is_finish(philo))
	{
		pthread_mutex_lock(&philo->core->arg.m_check);
		philo->nb_eat++;
		philo->last_eat = get_actual_time();
		time = philo->core->arg.t_eat * 1000;
		pthread_mutex_unlock(&philo->core->arg.m_check);
		usleep(time);
	}
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(&philo->left_f);
}

void	ft_sleeping(t_philo *philo)
{
	size_t	time;

	time = 0;
	philo_print(philo, SLEEP);
	if (!ft_is_finish(philo))
	{
		pthread_mutex_lock(&philo->core->arg.m_check);
		time = philo->core->arg.t_sleep * 1000;
		pthread_mutex_unlock(&philo->core->arg.m_check);
		usleep(time);
	}
}
