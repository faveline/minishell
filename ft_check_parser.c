/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:56:00 by faveline          #+#    #+#             */
/*   Updated: 2023/12/13 12:02:36 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_end_or(char *arg, int i)
{
	int	j;

	if (arg[i] == '&' || arg[i] == '|' || arg[i] == '<' || arg[i] == '>')
	{
		j = i - 1;
		while (j >= 0 && arg[j] == ' ')
			j--;
		if (j != i - 1 && (arg[j] == '&' || arg[j] == '|' || arg[j] == '('
					|| arg[j] == '<' || arg[j] == '>'))
			return (-1);
		if (j == i - 1 && (arg[j - 1] == '&' || arg[j - 1] == '|' || arg[j - 1] == '('
					|| arg[j - 1] == '<' || arg[j - 1] == '>'))
			return (-1);
	}
	return (1);
}

int ft_move_if_g_char(char *arg, int i)
{
	if (arg[i] == 39)
	{
		while (arg[i] && arg[i] != 39)
			i++;
	}
	else if (arg[i] == '"')
	{
		while (arg[i] && (arg[i] != '"'
			|| (arg[i - 1] == 92 && arg[i] == '"')))
			i++;
	}
	return (i);
}

static int	ft_check_p1(char *arg, int i)
{
	while (i >= 0 && (arg[i] == ' '
				|| arg[i] == '(' || arg[i] == ')'))
		i--;
	if (arg[i] == '&' || arg[i] == '|' || i == -1)
		return (1);
	else
		return (-1);
}

static int	ft_check_p2(char *arg, int i)
{
	while (arg[i] && (arg[i] == ' '
				|| arg[i] == '(' || arg[i] == ')'))
		i++;
	if (arg[i] == '&' || arg[i] == '|' || !arg[i])
		return (i);
	else
		return (-i);
}

int	ft_check_pars(char *arg)
{
	int	nbr_par;
	int	cpy;
	int	i;
	int	error;

	i = 0;
	cpy = 0;
	nbr_par = 0;
	while (arg && arg[i])
	{
		i = ft_move_if_g_char(arg, i);
		if (ft_check_end_or(arg, i) < 0)
			return (-i);
		if (arg[i] == '(')
		{
			if (ft_check_p1(arg, i) < 0)
				return (-i);
			cpy++;
			nbr_par++;
		}
		if (arg[i] == ')')
		{
			error = ft_check_p2(arg, i);
			if (error < 0)
				return (error);
			nbr_par--;
			if (nbr_par < 0)
				return (-i);
		}
		i++;
	}
	return (cpy);
}
