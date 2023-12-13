/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:43:48 by faveline          #+#    #+#             */
/*   Updated: 2023/12/13 15:18:25 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_nbr_cmd(t_arg *arg)
{
	int		nbr_cpy;
	int		i;

	i = 0;
	arg->nbr_cmd = 0;
	while (arg->input[i])
	{
		i = ft_move_if_g(arg, i);
		nbr_cpy = arg->nbr_par;
		if (arg->input[i] == '(')
		{
			while (arg->input[i] && nbr_cpy > 0)
			{
				if (arg->input[i] == ')')
					nbr_cpy--;
				else
					i++;
			}
			if (!arg->input[i])
				i--;
			arg->nbr_cmd++;
		}
		if (arg->input[i] == '&')
		{
			arg->nbr_cmd++;
			if (arg->input[i + 1] == '&')
				i++;
		}
		if (arg->input[i] == '|')
		{
			arg->nbr_cmd++;
			if (arg->input[i + 1] == '|')
				i++;
		}	
		i++;
	}
}

static int	ft_size_name(t_arg *arg, int i)
{
	int	size;
	int	j;

	size = 1;
	while (arg->input[i])
	{
		j = ft_move_if_g(arg, i);
		size = size + j - i;
		i = j;
		j = ft_move_if_p(arg, i);
		size = size + j - i;
		i = j;
		if (arg->input[i] == '&' || arg->input[i] == '|')
			return (size);
		size++;
		i++;
	}
	return (size);
}

static int	ft_ini_parser(t_arg *arg)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (arg->input[i])
	{
		j = 0;
		arg->parser[k].name = (char *)malloc((ft_size_name(arg, i) + 2) * sizeof(char));
		if (arg->parser[k].name == NULL)
			return (-1);
		while (arg->input[i] && arg->input[i] != '&' && arg->input[i] != '|')
		{
			arg->parser[k].name[j] = arg->input[i];
			j++;
			i++;
			ft_g_cases(arg, &i, &j, k);
			ft_p_cases(arg, &i, &j, k);
		}
		ft_ini_ope(arg, i, k);
		while (arg->input[i] && (arg->input[i] == '|' || arg->input[i] == '&'))
			i++;
		arg->parser[k].name[j] = '\0';
		k++;
	}
	arg->parser[k].name = NULL;
	return (1);
}

int	ft_parser(t_arg *arg)
{
	ft_nbr_cmd(arg);
	arg->parser = (t_cmd *)malloc((arg->nbr_cmd + 2) * sizeof(t_cmd));
	if (arg->parser == NULL)
		return (-1);
	if (ft_ini_parser(arg) < 0)
		return (-1);
	return (1);
}
