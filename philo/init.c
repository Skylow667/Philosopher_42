/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:15:31 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/15 12:59:27 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	tv_s;
	struct timezone	tv_u;
	int				time;

	gettimeofday(&tv_s, &tv_u);
	time = tv_s.tv_usec / 1000 + ((tv_s.tv_sec % 1000) * 1000);
	return (time);
}

void	init_philo(int i, t_philo *philo, struct s_pars *game)
{
	philo->id = i + 1;
	philo->nb_meal = 0;
	philo->last_meal = get_time();
	pthread_mutex_init(&philo->r_fork, NULL);
	philo->game = game;
	philo->alive = true;
	philo->eat_all = false;
}

void	init_game(t_pars *game, int argc, char **argv)
{
	game->nb_philo = ft_atoll(argv[1]);
	game->meal = 0;
	game->all_eat = false;
	game->time_to_die = ft_atoll(argv[2]);
	game->time_to_eat = ft_atoll(argv[3]);
	game->time_to_sleep = ft_atoll(argv[4]);
	game->time = get_time();
	game->dead = false;
	pthread_mutex_init(&game->printf, NULL);
	pthread_mutex_init(&game->meal_m, NULL);
	pthread_mutex_init(&game->alive_m, NULL);
	pthread_mutex_init(&game->dead_m, NULL);
	pthread_mutex_init(&game->time_m, NULL);
	if (argc == 6)
		game->total_meal = ft_atoll(argv[5]);
	else
		game->total_meal = -1;
	game->philo = malloc(game->nb_philo * sizeof(t_philo));
}
