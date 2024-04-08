/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:07:28 by aallou-v          #+#    #+#             */
/*   Updated: 2024/03/21 22:39:42 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	**reformed(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][j] == '+' && ft_strlen(argv[i]) > 1)
			j++;
		while (argv[i][j] == '0')
			j++;
		if (j != '0')
			argv[i] = &argv[i][j];
	}
	return (argv);
}

char	*parsing(int argc, char **argv, t_core *core)
{
	int	i;

	if (argc < 5 || argc > 6)
		return ("./philo <number_of_philo> <time_to_die> <time_to_eat> \
<time_to_sleep> [number_of_times_each_philo_must_eat]");
	argv = reformed(argc, argv);
	i = 0;
	while (++i < argc)
	{
		if (!ft_isonly(argv[i], "0123456789"))
			return ("Invalide Argument");
	}
	core->arg.n_philo = ft_atoul(argv[1]);
	if (core->arg.n_philo < 1 || core->arg.n_philo > 200)
		return ("Number of philosophers incorrect !");
	core->arg.t_die = ft_atoul(argv[2]);
	core->arg.t_eat = ft_atoul(argv[3]);
	core->arg.t_sleep = ft_atoul(argv[4]);
	core->arg.n_eat = -1;
	if (argc == 6)
		core->arg.n_eat = ft_atoul(argv[5]);
	core->philo = ft_calloc(core->arg.n_philo, sizeof(t_philo));
	if (!core->philo)
		return ("Malloc Error (core->philo)");
	return (NULL);
}
