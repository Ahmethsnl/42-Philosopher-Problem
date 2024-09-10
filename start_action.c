/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmsanli <ahmsanli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:36:44 by ahmsanli          #+#    #+#             */
/*   Updated: 2024/05/13 14:28:47 by ahmsanli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_data *data)
{
	int		i;
	t_time	time;

	i = 0;
	time = 0;
	while (i < data->philo_n)
	{
		if (pthread_create(&data->philo[i].thread, NULL, simulation,
				&data->philo[i]))
		{
			free_destroy(data);
			return (ft_exit("Thread create failed(start_simulation)\n"));
		}
		i++;
		usleep(100);
	}
	i = 0;
	return (monitor(data, time));
}

void	aristoteles(t_philo *phi)
{
	if (phi->data->philo_n == 1)
	{
		ft_sleep_time(phi, phi->data->death_timer);
		phi->data->corpse = 1;
	}
}

void	dinner_time(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->forks[ph->id]);
	ft_write(1, ph, "has taken a fork", ft_time() - ph->timer);
	aristoteles(ph);
	pthread_mutex_lock(&ph->data->forks[(ph->id + 1) % (ph->data->philo_n)]);
	ft_write(1, ph, "has taken a fork", ft_time() - ph->timer);
	checker(ph, 1);
	ft_write(2, ph, "eating", ft_time() - ph->timer);
	checker(ph, 2);
	if (ph->data->meal_timer <= ph->data->sleep_timer)
		ft_lastmeal(ph);
	ft_sleep_time(ph, ph->data->meal_timer);
	checker(ph, 2);
	if (ph->data->meal_timer > ph->data->sleep_timer)
		ft_lastmeal(ph);
	pthread_mutex_unlock(&ph->data->forks[ph->id]);
	pthread_mutex_unlock(&ph->data->forks[(ph->id + 1) % (ph->data->philo_n)]);
	ft_write(2, ph, "sleeping", ft_time() - ph->timer);
	ft_sleep_time(ph, ph->data->sleep_timer);
	checker(ph, 2);
	ft_write(2, ph, "thinking", ft_time() - ph->timer);
}

void	*simulation(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
		dinner_time(ph);
	return (SUCCESS);
}

int	monitor(t_data *data, t_time time)
{
	int	i;

	while (1)
	{
		i = 0;
		usleep(100);
		pthread_mutex_lock(data->death);
		time = ft_time() - data->philo->timer;
		i = ft_death_check(data->philo, time);
		if (i != -1)
			return (0);
		else if (data->ac == 6 && round_check(data))
			return (0);
		pthread_mutex_unlock(data->death);
	}
	return (0);
}
