/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:11:48 by faveline          #+#    #+#             */
/*   Updated: 2023/12/13 15:18:33 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ini_ope(t_arg *arg, int i, int k)
{
	if (arg->input[i] == '&')
		arg->parser[k].ope = '&';
	else if (arg->input[i] == '|' && arg->input[i + 1] == '|')
		arg->parser[k].ope = '|';
	else if (arg->input[i] == '|')
		arg->parser[k].ope = 'P';
	else if (!arg->input[i])
		arg->parser[k].ope = '0';
	arg->parser[k].ok = 1;
}

void	ft_g_cases(t_arg *arg, int *i, int *j, int k)
{
	int	x;
	int	y;

	x = *i;
	y = *j;
	if (arg->input[x] == 39)
	{
		arg->parser[k].name[y] = arg->input[x];
		y++;
		x++;
		while (arg->input[x] && arg->input[x] != 39)
		{
			arg->parser[k].name[y] = arg->input[x];
			y++;
			x++;
		}
	}
	else if (arg->input[x] == '"')
	{
		arg->parser[k].name[y] = arg->input[x];
		y++;
		x++;
		while (arg->input[x] && (arg->input[x] != '"'
					|| (arg->input[x - 1] == 92 && arg->input[x] == '"')))
		{
			arg->parser[k].name[y] = arg->input[x];
			y++;
			x++;
		}
	}
	*i = x;
	*j = y;
}

int	ft_move_if_p(t_arg *arg, int i)
{
	if (arg->input[i] == '(')
	{
		i++;
		while (arg->input[i] && arg->input[i] != ')')
		{
			i = ft_move_if_g(arg, i);
			i = ft_move_if_p(arg, i);
			if (arg->input[i])
				i++;
		}
		return (i);
	}
	else
		return (i);
}

void	ft_p_cases(t_arg *arg, int *i, int *j, int k)
{
	int	x;
	int	y;
	int	tmp;

	x = *i;
	y = *j;
	if (arg->input[x] == '(')
	{
		arg->parser[k].name[y] = arg->input[x];
		y++;
		x++;
		x = ft_move_if_g(arg, x);
		tmp = ft_move_if_p(arg, x);
		while (x <= tmp)
		{
			arg->parser[k].name[y] = arg->input[x];
			y++;
			x++;
		}
		while (arg->input[x] && arg->input[x] != ')')
		{
			arg->parser[k].name[y] = arg->input[x];
			y++;
			x++;
			x = ft_move_if_g(arg, x);
		}
	}
	*i = x;
	*j = y;
}
