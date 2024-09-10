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

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	data->death = malloc(sizeof(pthread_mutex_t));
	if (data->forks == 0 || data->death == 0)
	{
		free(data);
		free(data->philo);
		return (ft_exit("Fork or Death allocate is failed(mutex_init)\n"));
	}
	while (i < data->philo_n)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(data->death, NULL);
	return (SUCCESS);
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
