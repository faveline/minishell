/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:27:38 by faveline          #+#    #+#             */
/*   Updated: 2023/12/13 11:24:14 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_cut_pwd(char *pwd)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	j = 0;
	i = 0;
	size = 0;
	while (pwd[i])
		i++;
	while (pwd[--i] != '/')
		size++;
	while (pwd[--i] != '/')
		size++;
	str = (char *)malloc((size + 2) * sizeof(char));
	if (str == NULL)
		return (free(pwd), NULL);
	while (pwd[++i])
	{
		str[j] = pwd[i];
		j++;
	}
	str[j] = '\0';
	free(pwd);
	return (str);
}

static char	*ft_display_prompt(void)
{
	char	buffer[1000];
	char	*pwd;

	pwd = getcwd(buffer, 1000);
	if (pwd == NULL)
		return (perror("Issue getting the current dir"), NULL);
	pwd = ft_strjoin(pwd, " $ ");
	if (pwd == NULL)
		return (ft_error_ms(error_malloc), NULL);
	pwd = ft_cut_pwd(pwd);
	if (pwd == NULL)
		return (ft_error_ms(error_malloc), NULL);
	return (pwd);
}

int	ft_read_prompt(t_arg *arg)
{
	char	*input;
	char	*str;
	int		j;

	str = ft_display_prompt();
	if (str == NULL)
		return (-1);
	arg->input = readline(str);
	free(str);
	while (arg->input)
	{
		j = -1;
		add_history(arg->input);
		arg->nbr_par = ft_check_pars(arg->input);
		if (arg->nbr_par < 0)
		{
			ft_error_ms(error_parse);
			ft_printf("near %c\n", arg->input[-arg->nbr_par]);
		}
		else 
		{
			if (ft_parser(arg) < 0)
				ft_error_ms(error_malloc);
			while (arg->parser[++j].name)
				printf("%s\n", arg->parser[j].name);
			ft_exterminate(arg);
		}
		str = ft_display_prompt();
		if (str == NULL)
			return (-1);
		arg->input = readline(str);
		free(str);
	}
	return (1);
}
