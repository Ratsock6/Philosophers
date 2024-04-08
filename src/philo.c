/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:28:36 by aallou-v          #+#    #+#             */
/*   Updated: 2024/04/01 17:12:18 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_is_alone(t_philo *philo)
{
	bool	is_alone;

	is_alone = false;
	pthread_mutex_lock(&philo->core->arg.m_check);
	if (philo->core->arg.n_philo == 1)
		is_alone = true;
	pthread_mutex_unlock(&philo->core->arg.m_check);
	return (is_alone);
}

bool	ft_is_finish(t_philo *philo)
{
	bool	is_finish;

	pthread_mutex_lock(&philo->core->arg.m_check);
	is_finish = philo->core->arg.finish;
	pthread_mutex_unlock(&philo->core->arg.m_check);
	return (is_finish);
}

void	*ft_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!ft_is_finish(philo))
	{
		if (!ft_is_finish(philo))
			ft_take_fork(philo);
		if (!ft_is_alone(philo))
			ft_eating(philo);
		if (!ft_is_finish(philo))
			ft_sleeping(philo);
		if (!ft_is_finish(philo))
			philo_print(philo, THINK);
	}
	return (NULL);
}

int	start(t_core *core)
{
	size_t	i;
	size_t	j;
	int		check;

	i = -1;
	j = core->arg.n_philo;
	core->arg.start_t = get_actual_time();
	while (++i < j)
	{
		check = pthread_create(&core->philo[i].thread_id, NULL, ft_philo \
			, &core->philo[i]);
		if (check != 0)
			return (0);
	}
	ft_check(core);
	i = 0;
	while (i < j)
	{
		pthread_join(core->philo[i].thread_id, NULL);
		i++;
	}
	return (1);
}
