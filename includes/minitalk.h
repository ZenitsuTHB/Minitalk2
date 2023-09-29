/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:30:49 by avolcy            #+#    #+#             */
/*   Updated: 2023/09/29 17:28:03 by avolcy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

/*************INCLUDES******************/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../libft/libft.h"
/**************************************/

/***********COLORS*****************/
# define RED		"\033[0;31m" 
# define BLUE 		"\033[0;36m"
# define GREEN 		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define B_WHITE	"\033[1;37m"
# define DEF_COLOR	"\033[0m"
/********************************/

/*****************STRUCTURE*****************/
typedef struct s_data
{
	int		i;
	int		flag;
	int		octet;
	int		str_len;
	char	*string;
	int		current_bit;
}t_data;
//........GLOBAL_VAR..........//
	t_data	g_data;
/*******************************************/


/*************************ERROR_MESSAGES********************************/
#define INVALID_PID_ERR "Invalid PID !\n"
#define PID_EXAMPLE "PID example : 1xxx1"
#define ERR_SENDING_MSG "Message sending failed !\n"
#define MAN_SIGNAL "Read man 'signal.h' for more.\n"
#define INVALID_ARG_ERR "Invalid number of arguments !\n"
#define URS1_FAIL "Failed to setup the signal handler for SIGUSR1 !\n"
#define USR2_FAIL "Failed to setup the signal handler for SIGUSR2 !\n"
#define USAGE_MESSAGE "Usage : ./client <server PID> <string to send>\n"
/***********************************************************************/
#endif
