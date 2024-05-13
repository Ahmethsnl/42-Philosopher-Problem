/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmsanli <ahmsanli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:46:18 by ahmsanli          #+#    #+#             */
/*   Updated: 2024/05/13 14:29:17 by ahmsanli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_checknum(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+')
		i++;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ft_exit("check arguments (checknum)\n"));
		i++;
	}
	return (SUCCESS);
}

int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		data->philo[i].id = i;
		data->philo[i].data = data;
		data->philo[i].timer = ft_time();
		data->philo[i].last_meal = ft_time();
		if (data->ac == 6 && data->round <= 0)
		{
			free(data);
			free(data->philo);
			return (ft_exit("check arguments(philo_init)\n"));
		}
		i++;
	}
	return (SUCCESS);
}

int	round_check(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		if (data->philo[i].c_eat != data->round)
			return (SUCCESS);
		i++;
	}
	return (ERROR);
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

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 5 || ac == 6)
	{
		data = malloc (sizeof * data);
		if (data == 0)
			return (ft_exit("data allocate failed\n"));
		if (data_init(data, ac, av))
			return (ERROR);
		if (philo_init(data))
			return (ERROR);
		if (mutex_init(data))
			return (ERROR);
		if (start_simulation(data))
			return (ERROR);
		free_destroy(data);
		return (0);
	}
	else
		return (ft_exit("check arguments(main)\n"));
	return (SUCCESS);
}
