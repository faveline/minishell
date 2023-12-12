/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_ms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:53:19 by faveline          #+#    #+#             */
/*   Updated: 2023/12/12 18:11:35 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_ms(int error)
{
	if (error == -1)
		ft_printf("Problem with malloc\n");
	else if (error == -2)
		ft_printf("Parsing error\n");
}

int	ft_move_if_g(t_arg *arg, int i)
{
	if (arg->input[i] == 39)
	{
		while (arg->input[i] && arg->input[i] != 39)
			i++;
		i++;
	}
	else if (arg->input[i] == '"')
	{
		while (arg->input[i] && (arg->input[i] != '"'
					|| (arg->input[i - 1] == 92 && arg->input[i] == '"')))
			i++;
		i++;
	}
	return (i);
}

void	ft_exterminate(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg->parser && arg->parser[i].name)
	{
		free(arg->parser[i].name);
		i++;
	}
	free(arg->parser);
	free(arg->input);
}
