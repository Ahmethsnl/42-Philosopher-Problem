/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmsanli <ahmsanli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:20:51 by ahmsanli          #+#    #+#             */
/*   Updated: 2024/05/13 14:30:33 by ahmsanli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write(int action, t_philo *ph, char *str, t_time time)
{
	pthread_mutex_lock(ph->data->death);
	if (ph->data->corpse == 0)
	{
		if (action == 1)
			printf("%llu %d %s\n", time, ph->id + 1, str);
		else
			printf("%llu %d is %s\n", time, ph->id + 1, str);
	}
	pthread_mutex_unlock(ph->data->death);
}

void	free_destroy(t_data *data)
{
	pthread_mutex_destroy(data->death);
	pthread_mutex_destroy(data->forks);
	free(data->philo);
	free(data);
}

void	ft_lastmeal(t_philo *philo)
{
	pthread_mutex_lock(philo->data->death);
	philo->last_meal = ft_time();
	pthread_mutex_unlock(philo->data->death);
}

int	ft_exit(char *str)
{
	printf("%s", str);
	return (1);
}

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
