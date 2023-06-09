/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:56:59 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/15 12:58:31 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	print_philo(philo, BLUE, FORK_R);
	pthread_mutex_lock(philo->l_fork);
	print_philo(philo, BLUE, FORK_L);
	print_philo(philo, GREEN, EATING);
	pthread_mutex_lock(&philo->game->meal_m);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->game->meal_m);
	ft_usleep(philo->game->time_to_eat, philo);
	pthread_mutex_lock(&philo->game->dead_m);
	if (philo->game->dead == false && philo->alive == true)
	{
		pthread_mutex_lock(&philo->game->meal_m);
		philo->nb_meal++;
		if (philo->nb_meal == philo->game->total_meal)
			philo->eat_all = true;
		pthread_mutex_unlock(&philo->game->meal_m);
	}
	pthread_mutex_unlock(&philo->game->dead_m);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	sleep_routine(t_philo *philo)
{
	print_philo(philo, PINK, SLEEP);
	ft_usleep(philo->game->time_to_sleep, philo);
}

int	sleep_philo(t_philo *philo)
{
	if (philo->id % 2 != 0)
		usleep(5000);
	if (philo->game->nb_philo == 1)
	{
		print_philo(philo, BLUE, FORK_R);
		return (1);
	}
	return (0);
}

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (sleep_philo(philo) == 1)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->game->dead_m);
		pthread_mutex_lock(&philo->game->meal_m);
		if (philo->game->dead == true
			|| philo->game->all_eat == true || philo->alive == false)
		{
			pthread_mutex_unlock(&philo->game->meal_m);
			pthread_mutex_unlock(&philo->game->dead_m);
			break ;
		}
		pthread_mutex_unlock(&philo->game->meal_m);
		pthread_mutex_unlock(&philo->game->dead_m);
		eat_routine(philo);
		sleep_routine(philo);
		print_philo(philo, YELLOW, THINK);
	}
	return (NULL);
}
