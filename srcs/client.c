/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:27:47 by avolcy            #+#    #+#             */
/*   Updated: 2023/09/30 22:05:32 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include "../libft/libft.h"

/*==============Explaination================*/
/*	Only 2 arguments 						*/
/*	1st PID of the server8					*/
/*	2nd the data to print in the server.	*/
/*==========================================*/

/***************CHECK_ERROR*************************************/
static	void	ft_error_arg(int ac, char **av)
{
	int		i;

	i = 0;
	if (ac != 3)
		ft_error_handling(INVALID_ARG_ERR, USAGE_MESSAGE);
	while (av[1][i])
		if (!ft_isdigit(av[1][i++]) || ft_strlen(av[1]) < 4 || av[1] <= 0)
			ft_error_handling(INVALID_PID_ERR, PID_EXAMPLE);
}
/***************************************************************/

/*****************SEND_STR_LENGTH******************/
static	void	ft_send_strlen(pid_t pid, int len)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (len & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		len = len >> 1;
		i++;
		usleep(100);
	}
}
/****************************************************/

/********************DATA_SENDER_FUNCTION************************************/
static int	ft_send_msg(pid_t sv_pid, unsigned char c)
{
	int	idx_bit;

	idx_bit = 0;
	while (idx_bit < 8)
	{
		if (kill(sv_pid, 0) != 0)
		{
			ft_putstr_fd(RED"Server unreachable or, process STOPPED !\n", 1);
			exit(EXIT_FAILURE);
		}
		if ((c & 1 << idx_bit) == 0)
			kill(sv_pid, SIGUSR1);
		else
			kill(sv_pid, SIGUSR2);
		usleep(100);
		idx_bit++;
	}
	return (0);
}
/****************************************************************************/

/**********************MAIN**************************/
int	main(int argc, char **argv)
{
	int		i;
	pid_t	sv_pid;
	char	*str;

	i = 0;
	ft_error_arg(argc, argv);
	sv_pid = ft_atoi(argv[1]);
	str = argv[2];
	ft_send_strlen(sv_pid, ft_strlen(str));
	ft_putstr_fd(YELLOW"-- Sending ", 1);
	ft_putnbr_fd(ft_strlen(str), 1);
	ft_putstr_fd(YELLOW" bytes... --\n"DEF_COLOR, 1);
	while (str[i])
	{
		if (ft_send_msg(sv_pid, str[i]) == -1)
			return (0);
		else
			i++;
	}
	ft_send_msg(sv_pid, str[i]);
	return (0);
}
/****************************************************/
