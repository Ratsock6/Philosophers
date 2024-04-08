/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:39:00 by cjouenne          #+#    #+#             */
/*   Updated: 2024/03/29 21:03:38 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"
# include <stdbool.h>
# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	bool				available;
}				t_fork;

typedef struct s_arg
{
	size_t					n_philo;
	long					n_eat;
	long					t_die;
	size_t					t_eat;
	size_t					t_sleep;
	long					start_t;
	pthread_mutex_t			write;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_wait;
	pthread_mutex_t			m_finish;
	pthread_mutex_t			m_check;
	bool					finish;
	size_t					n_philo_finish;
	size_t					stop;
}							t_arg;

typedef struct s_philo
{
	size_t				id;
	pthread_t			thread_id;
	pthread_t			thread_death_id;
	pthread_mutex_t		*right_f;
	pthread_mutex_t		left_f;
	struct s_core		*core;	
	long				last_eat;
	unsigned int		nb_eat;
	bool				is_finish;
	char				*name;
}						t_philo;

typedef struct s_core
{
	struct s_philo	*philo;
	struct s_arg	arg;
}	t_core;

typedef enum e_states
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_states;

size_t	ft_atoul(char *s);
char	*parsing(int argc, char **argv, t_core *core);
void	init_philo(t_core *core);
long	get_actual_time(void);
long	get_time(t_core *core);
void	philo_print(t_philo *philo, t_states states);
bool	is_dead(t_philo *philo);
void	ft_exit(t_core *core);

void	ft_check(t_core *core);
bool	ft_is_finish(t_philo *philo);
void	ft_take_fork(t_philo *philo);
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
int		start(t_core *core);

#endif
