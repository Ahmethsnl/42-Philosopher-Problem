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

int	data_init(t_data *data, int ac, char **av)
{
	int	i;

	i = 1;
	data->ac = ac;
	while (i < data->ac)
	{
		if (ft_checknum(av[i]))
			return (ERROR);
		i++;
	}
	data->philo_n = ft_atoi(av[1]);
	data->death_timer = ft_atoi(av[2]);
	data->meal_timer = ft_atoi(av[3]);
	data->sleep_timer = ft_atoi(av[4]);
	data->av = av;
	if (data->philo_n <= 0 || data->death_timer <= 0 || data->sleep_timer <= 0
		|| data->meal_timer <= 0)
		return (ft_exit("invalid arguments(data_init)"));
	data->philo = malloc(sizeof(t_philo) * data->philo_n);
	if (data->philo == 0)
	{
		free(data);
		return (ft_exit("Fail Allocate(data_init)"));
	}
	return (SUCCESS);
}
