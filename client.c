/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexigar <alexigar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:58:46 by alexigar          #+#    #+#             */
/*   Updated: 2024/05/29 11:23:53 by alexigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

char	*convert_char(char c)
{
	int		value;
	char	*binary;
	int		i;

	i = 7;
	value = (int) c;
	binary = malloc(9);
	if (!binary)
		return (NULL);
	while (value)
	{
		binary[i] = (value % 2) + '0';
		value = value / 2;
		i--;
	}
	while (i >= 0)
	{
		binary[i] = '0';
		i--;
	}
	return (binary);
}

char	*to_bin(char *message)
{
	char	*to_return;
	char	*converted;
	int		i;
	int		j;

	to_return = malloc((ft_strlen(message)) * 8 + 1);
	if (!to_return)
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (message[++i])
	{
		converted = convert_char(message[i]);
		if (!converted)
		{
			free(to_return);
			exit(EXIT_FAILURE);
		}
		ft_memcpy(to_return + j, converted, 8);
		free(converted);
		converted = NULL;
		j += 8;
	}
	to_return[j] = '\0';
	return (to_return);
}

void	send_eom(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		i++;
		usleep(50);
	}
}

void	send_message(int pid, char *binary)
{
	int	i;
	int	letter_flag;

	i = 0;
	letter_flag = 0;
	while (binary[i] != '\0')
	{
		if (binary[i] == '0')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(50);
		letter_flag++;
		if (letter_flag == 8)
		{
			usleep(50);
			letter_flag = 0;
		}
	}
	send_eom(pid);
	free(binary);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;
	char	*binary;

	if (argc != 3 || argv[2][0] == '\0')
		exit(EXIT_FAILURE);
	else
	{
		pid = ft_atoi(argv[1]);
		message = argv[2];
	}
	binary = to_bin(message);
	send_message(pid, binary);
}
