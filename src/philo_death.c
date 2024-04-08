/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 21:02:41 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/29 21:00:23 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_check_max_eat(t_core *core)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&core->arg.m_check);
	while (i < core->arg.n_philo)
	{
		if (core->philo[i].nb_eat < core->arg.n_eat)
		{
			pthread_mutex_unlock(&core->arg.m_check);
			return (false);
		}
		i++;
	}
	core->arg.finish = true;
	pthread_mutex_unlock(&core->arg.m_check);
	return (true);
}

static bool	ft_p_is_finish(t_core *core)
{
	bool	is_finish;

	pthread_mutex_lock(&core->arg.m_check);
	is_finish = core->arg.finish;
	pthread_mutex_unlock(&core->arg.m_check);
	return (is_finish);
}

static size_t	ft_p_get_ph(t_core *core)
{
	size_t	i;

	pthread_mutex_lock(&core->arg.m_check);
	i = core->arg.n_philo;
	pthread_mutex_unlock(&core->arg.m_check);
	return (i);
}

static void	ft_launch_eat(t_core *core)
{
	pthread_mutex_lock(&core->arg.m_check);
	if (core->arg.n_eat != -1)
	{
		pthread_mutex_unlock(&core->arg.m_check);
		if (ft_check_max_eat(core))
		{
			pthread_mutex_lock(&core->arg.m_check);
			core->arg.finish = true;
			pthread_mutex_unlock(&core->arg.m_check);
		}
	}
	else
		pthread_mutex_unlock(&core->arg.m_check);
}

void	ft_check(t_core *core)
{
	size_t	i;

	while (!ft_p_is_finish(core))
	{
		i = 0;
		ft_launch_eat(core);
		while (i < ft_p_get_ph(core) && !ft_p_is_finish(core))
		{
			pthread_mutex_lock(&core->arg.m_check);
			if (get_actual_time() - core->philo[i].last_eat >= \
				core->arg.t_die)
			{
				pthread_mutex_unlock(&core->arg.m_check);
				philo_print(&core->philo[i], DEAD);
				pthread_mutex_lock(&core->arg.m_check);
				core->arg.finish = true;
				pthread_mutex_unlock(&core->arg.m_check);
				return ;
			}
			pthread_mutex_unlock(&core->arg.m_check);
			i++;
		}
	}
}
