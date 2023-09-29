/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:28:00 by avolcy            #+#    #+#             */
/*   Updated: 2023/09/29 13:52:32 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
/*============================================================================*/
/*new_siga.sa_sigaction														  */
/*Assigns the signal handler function handle_sigusr to the 					  */
/*sa_sigaction field of the sa_newsig structure  							  */
/*sa_newsig.sa_flags = SA_SIGINFO;											  */
/*Sets the sa_flags field of the sa_newsig structure to SA_SIGINFO. 		  */
/*This flag indicates that the sa_sigaction field points to a function... 	  */
/*that takes three arguments												  */
/*Initialize new_siga.sa_flags, indicate that the sa_sigaction field... 	  */
/*points to a function with extended signal information.					  */
/*new_siga.sa_sigaction= &ft_handle_sigusr;Specify the signal handler function*/
/*============================================================================*/
t_data	g_data;

static void	ft_rebuild_string_len(int signal)
{
	if (signal == SIGUSR2)
		g_data.str_len = (g_data.str_len | 1 << g_data.current_bit);
	if (g_data.current_bit == 31)
	{
		g_data.flag = 1;
		g_data.string = ft_calloc((g_data.str_len + 1), sizeof(char));
		if (g_data.string == NULL)
		{
			ft_putstr_fd(RED"Memory allocation failed!\n"DEF_COLOR, 1);
			return ;
		}
		g_data.current_bit = 0;
		g_data.str_len = 0;
		return ;
	}
	(g_data.current_bit)++;
}

static void	ft_print_and_reset(void)
{
	int	j;

	j = 0;
	while (g_data.string[j] != '\0')
	{
		write(1, &(g_data.string[j]), 1);
		j++;
	}
	write(1, "\n", 1);
	ft_putstr_fd(BLUE"-- ", 1);
	ft_putnbr_fd(j, 1);
	ft_putstr_fd(" bytes displayed --\n"DEF_COLOR, 1);
	free(g_data.string);
	g_data.string = NULL;
	g_data.str_len = 0;
	g_data.octet = 0;
	g_data.current_bit = 0;
	g_data.i = 0;
	g_data.flag = 0;
	return ;
}

static void	ft_rebuild_char(int signal)
{
	if (signal == SIGUSR2)
		g_data.octet = (g_data.octet | 1 << g_data.current_bit);
	if (g_data.current_bit == 7)
	{
		g_data.string[g_data.i] = g_data.octet;
		(g_data.i)++;
		g_data.current_bit = 0;
		if (g_data.octet == '\0')
			ft_print_and_reset();
		g_data.octet = 0;
		return ;
	}
	(g_data.current_bit)++;
}

void	ft_handle_sigusr(int signal, siginfo_t *info, void *context)
{
	pid_t	client_pid;

	(void)context;
	client_pid = 0;
	client_pid = info->si_pid;
	if (g_data.flag == 0)
		ft_rebuild_string_len(signal);
	else
		ft_rebuild_char(signal);
}

int	main(void)
{
	int					tmp;
	struct sigaction	new_sig;

	ft_putstr_fd(GREEN"SERVER's PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n"DEF_COLOR, 1);
	new_sig.sa_sigaction = ft_handle_sigusr;
	new_sig.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &new_sig, NULL);
	sigaction(SIGUSR2, &new_sig, NULL);
	while (1)
	{
		tmp = g_data.current_bit;
		sleep(1);
		if (g_data.current_bit == tmp)
		{
			g_data.i = 0;
			g_data.flag = 0;
			g_data.octet = 0;
			g_data.str_len = 0;
			free(g_data.string);
			g_data.string = NULL;
			g_data.current_bit = 0;
		}
	}
}
