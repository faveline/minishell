/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:51:43 by faveline          #+#    #+#             */
/*   Updated: 2023/12/12 18:10:19 by faveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>

# define error_malloc (-1)
# define error_parse (-2)

typedef struct s_cmd
{
	char	*name;
	char	*cmd;
	char	*file;
	char	ope;
	int		ok;
	int		par;
}			t_cmd;

typedef struct s_arg
{
	char	*input;
	int		nbr_par;
	t_cmd	*parser;
	int		nbr_cmd;
}			t_arg;

int		ft_check_pars(char *arg);
int		ft_read_prompt(t_arg *arg);
void	ft_error_ms(int error);
int		ft_move_if_g(t_arg *arg, int i);
int		ft_parser(t_arg *arg);
void	ft_exterminate(t_arg *arg);

#endif
