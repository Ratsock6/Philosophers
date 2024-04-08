/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:12:05 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/28 21:18:43 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_name(size_t id)
{
	if (id == 1)
		return ("aallou-v");
	if (id == 2)
		return ("nlaerema");
	if (id == 3)
		return ("sdemaude");
	if (id == 4)
		return ("daleliev");
	if (id == 5)
		return ("ccormon");
	if (id == 6)
		return ("tlegend");
	if (id == 7)
		return ("ekoubbi");
	if (id == 8)
		return ("vsoltys");
	if (id == 9)
		return ("cejin");
	if (id > 10)
		return (get_name(id / 10));
	return ("mgallais");
}

void	init_mutex(t_core *core)
{
	pthread_mutex_init(&core->arg.write, NULL);
	pthread_mutex_init(&core->arg.dead, NULL);
	pthread_mutex_init(&core->arg.time_wait, NULL);
	pthread_mutex_init(&core->arg.m_finish, NULL);
	pthread_mutex_init(&core->arg.m_check, NULL);
}

void	init_philo(t_core *core)
{
	size_t	i;

	core->arg.stop = 0;
	core->arg.n_philo_finish = 0;
	core->arg.finish = false;
	core->arg.start_t = get_actual_time();
	init_mutex(core);
	i = -1;
	while (++i < core->arg.n_philo)
	{
		core->philo[i].id = i + 1;
		core->philo[i].last_eat = get_actual_time();
		core->philo[i].nb_eat = 0;
		core->philo[i].is_finish = false;
		core->philo[i].right_f = NULL;
		core->philo[i].name = get_name(i + 1);
		core->philo[i].core = core;
		pthread_mutex_init(&core->philo[i].left_f, NULL);
		if (i != 0)
			core->philo[i - 1].right_f = &core->philo[i].left_f;
	}
	core->philo[i - 1].right_f = &core->philo[0].left_f;
}
