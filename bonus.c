/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:13:18 by rtakashi          #+#    #+#             */
/*   Updated: 2023/06/15 14:14:56 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include "pipex.h"

static void	b_child(t_args args, int p[], char **e_path)
{
	if (args.cmd_cnt == 0)
		first_child(args, p, e_path);
	if (args.cmd_cnt == args.cmd_total - 1)
		last_child(args, p, e_path);
	else
		main_child(args, p, e_path);
}

static void	b_parent(int p[], char **e_path)
{
	if (dup2(p[0], STDIN_FILENO) < 0)
		free_perror_exit("dup2", e_path, NULL);
	if (close(p[0]) < 0)
		free_perror_exit("close", e_path, NULL);
	if (close(p[1]) < 0)
		free_perror_exit("close", e_path, NULL);
}

static void	loop_pipe_fork(t_args args, char **e_path)
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
			b_child(args, p, e_path);
		else
			b_parent(p, e_path);
		args.cmd_cnt++;
		args.cmd_index++;
	}
}

static void	heredoc(t_args *args, char **e_path)
{
	int		p[2];
	pid_t	pid;

	do_heredoc(*args, e_path);
	args->cmd_index = 3;
	args->cmd_total = args->argc - 4;
	while (args->cmd_cnt < args->cmd_total)
	{
		if (pipe(p) < 0)
			free_perror_exit("pipe", e_path, NULL);
		pid = fork();
		if (pid < 0)
			free_perror_exit("fork", e_path, NULL);
		if (pid == 0)
			child_heredoc(*args, p, e_path);
		else
			parent_heredoc(p, e_path);
		args->cmd_cnt++;
		args->cmd_index++;
	}
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q pipex_bonus");
// }

int	main(int argc, char **argv, char **envp)
{
	char	**e_path;
	t_args	args;

	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", HERE_DOC_LEN) == 0
			&& argc < 6))
	{
		ft_putstr_fd("invalid argment\n", 2);
		return (0);
	}
	args = args_init(argc, argv, envp);
	e_path = get_envp_path(envp);
	if (e_path == NULL)
		free_perror_exit("failed to get e_path", NULL, NULL);
	if (ft_strncmp(argv[1], "here_doc", HERE_DOC_LEN) == 0)
		heredoc(&args, e_path);
	else
		loop_pipe_fork(args, e_path);
	while (args.cmd_total > 0)
	{
		if (wait(NULL) < 0)
			free_perror_exit("wait", e_path, NULL);
		args.cmd_total--;
	}
	ft_free(e_path);
	return (0);
}
