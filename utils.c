/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmsanli <ahmsanli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:34:10 by ahmsanli          #+#    #+#             */
/*   Updated: 2024/05/13 14:28:57 by ahmsanli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	long	sign;
	long	result;
	long	i;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		result = (result * 10) + (str[i] - 48) * sign;
		if (result > 2147483647)
			return (0);
		if (result < -2147483648)
			return (-1);
		i++;
	}
	return (result);
}

t_time	ft_time(void)
{
	struct timeval	_timeval;
	t_time			time;

	gettimeofday(&_timeval, NULL);
	time = _timeval.tv_sec * 1000 + _timeval.tv_usec / 1000;
	return (time);
}

void	ft_sleep_time(t_philo *phi, int ttime)
{
	t_time	time;

	time = ft_time();
	if ((t_time)phi->data->death_timer < (time - phi->last_meal)
		+ (t_time)ttime)
	{
		ttime = phi->data->death_timer - (time - phi->last_meal);
		while (ft_time() - time <= (t_time)ttime)
			usleep(100);
	}
	else
	{
		while (ft_time() - time < (t_time)ttime)
			usleep(100);
	}
}

void	checker(t_philo *philo, int checker)
{
	pthread_mutex_lock(philo->data->death);
	if (checker == 1)
	{
		if (philo->data->ac == 6 && philo->c_eat < philo->data->round)
			philo->c_eat++;
	}
	else
	{
		if (philo->data->death_timer < (int)(ft_time() - philo->last_meal))
		{
			philo->data->corpse = 1;
		}
	}
	pthread_mutex_unlock(philo->data->death);
}

int	ft_death_check(t_philo *philo, t_time time)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_n)
	{
		if (philo->data->corpse == 1 && (int)time > philo->data->death_timer)
		{
			usleep(100);
			printf("%llu %d died\n", time, i + 1);
			return (i);
		}
		i++;
	}
	return (-1);
}
