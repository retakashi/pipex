/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:14:18 by reira             #+#    #+#             */
/*   Updated: 2023/06/15 14:11:36 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

static void	m_child(t_args args, int p[], char **e_path)
{
	if (args.cmd_cnt == 0)
		first_child(args, p, e_path);
	else
		last_child(args, p, e_path);
}

static void	m_parent(int p[], char **e_path)
{
	if (dup2(p[0], STDIN_FILENO) < 0)
		free_perror_exit("dup2", e_path, NULL);
	if (close(p[0]) < 0)
		free_perror_exit("close", e_path, NULL);
	if (close(p[1]) < 0)
		free_perror_exit("close", e_path, NULL);
}

static void	do_pipe_fork(t_args args, char **e_path)
{
	int		p[2];
	pid_t	pid;

	while (args.cmd_cnt < args.cmd_total)
	{
		if (pipe(p) < 0)
			free_perror_exit("pipe", e_path, NULL);
		pid = fork();
		if (pid < 0)
			free_perror_exit("fork", e_path, NULL);
		if (pid == 0)
			m_child(args, p, e_path);
		else
			m_parent(p, e_path);
		args.cmd_cnt++;
		args.cmd_index++;
	}
}

// __attribute__((destructor)) static void destructor()
// {
// system("leaks -q pipex");
// }

int	main(int argc, char **argv, char **envp)
{
	t_args	args;
	char	**e_path;

	if (argc != 5)
	{
		ft_putstr_fd("invalid argument\n", 2);
		return (0);
	}
	args = args_init(argc, argv, envp);
	e_path = get_envp_path(envp);
	if (e_path == NULL)
		free_perror_exit("failed to get e_path", NULL, NULL);
	do_pipe_fork(args, e_path);
	ft_free(e_path);
	while (args.cmd_total > 0)
	{
		if (wait(NULL) < 0)
			free_perror_exit("wait", e_path, NULL);
		args.cmd_total--;
	}
	return (0);
}
