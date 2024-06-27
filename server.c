/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexigar <alexigar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:57:56 by alexigar          #+#    #+#             */
/*   Updated: 2024/05/29 11:57:29 by alexigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

int	powered(int num, int power)
{
	if (power == 0)
		return (1);
	else if (power == 1)
		return (num);
	else
		return (num * powered(num, power - 1));
}

void	signal_handler(int signum)
{
	static int	to_print = 0;
	static int	bits_read = 0;
	static int	zero_read = 0;

	if (signum == SIGUSR1)
	{
		zero_read++;
	}
	else if (signum == SIGUSR2)
	{
		to_print += powered(2, (7 - bits_read));
		zero_read = 0;
	}
	bits_read++;
	if (zero_read == 8)
		ft_putchar_fd('\n', 1);
	if (bits_read == 8)
	{
		ft_putchar_fd(to_print, 1);
		bits_read = 0;
		to_print = 0;
		zero_read = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("%d\n", getpid());
	action.sa_handler = signal_handler;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (0);
}
