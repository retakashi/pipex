/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:41:20 by reira             #+#    #+#             */
/*   Updated: 2023/06/12 20:21:17 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include "pipex.h"

void	do_heredoc(t_args args, char **e_path)
{
	t_heredoc	here;

	here.flg = 0;
	here.limit_len = ft_strlen(args.argv[2]);
	args.in_fd = open(".heredoc_file", O_WRONLY | O_CREAT | O_TRUNC,
			S_IREAD | S_IWRITE);
	if (args.in_fd < 0)
		free_perror_exit(".heredoc_file", e_path, NULL);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		here.line = get_next_line(STDOUT_FILENO, &(here.flg));
		if (here.flg == 0 && here.line == NULL)
			free_perror_exit(NULL, e_path, NULL);
		if ((here.flg == 1 && here.line == NULL) || (ft_strncmp(here.line,
					args.argv[2], here.limit_len) == 0
				&& here.line[here.limit_len] == '\n'))
			break ;
		ft_putstr_fd(here.line, args.in_fd);
		free(here.line);
	}
	if (here.line != NULL)
		free(here.line);
	if (close(args.in_fd) < 0)
		free_perror_exit("close", e_path, NULL);
}

static void	read_heredoc(t_args args, int p[], char **e_path)
{
	args.in_fd = open(".heredoc_file", O_RDONLY);
	if (unlink(".heredoc_file") < 0)
		free_perror_exit("unlink", e_path, NULL);
	if (args.in_fd < 0)
		free_perror_exit(".heredoc_file", e_path, NULL);
	if (dup2(args.in_fd, STDIN_FILENO) < 0)
		free_perror_exit("dup2", e_path, NULL);
	if (close(args.in_fd) < 0)
		free_perror_exit("close", e_path, NULL);
	main_child(args, p, e_path);
}

static void	write_heredoc(t_args args, int p[], char **e_path)
{
	int	out_fd;

	out_fd = open(args.argv[args.argc - 1], O_RDWR | O_CREAT | O_APPEND,
			S_IREAD | S_IWRITE);
	if (out_fd < 0)
		free_perror_exit(args.argv[args.argc - 1], e_path, NULL);
	if (dup2(p[1], STDOUT_FILENO) < 0)
		free_perror_exit("dup2", e_path, NULL);
	if (close(p[0]) < 0)
		free_perror_exit("close", e_path, NULL);
	if (close(p[1]) < 0)
		free_perror_exit("close", e_path, NULL);
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		free_perror_exit("dup2", e_path, NULL);
	if (close(out_fd) < 0)
		free_perror_exit("close", e_path, NULL);
	get_cmdpath_exec(args, args.cmd_index, e_path);
}

void	child_heredoc(t_args args, int p[], char **e_path)
{
	if (args.cmd_cnt == 0)
		read_heredoc(args, p, e_path);
	if (args.cmd_cnt == args.cmd_total - 1)
		write_heredoc(args, p, e_path);
	else
		main_child(args, p, e_path);
}

void	parent_heredoc(int p[], char **e_path)
{
	if (dup2(p[0], STDIN_FILENO) < 0)
		free_perror_exit("dup2", e_path, NULL);
	if (close(p[1]) < 0)
		free_perror_exit("close", e_path, NULL);
	if (close(p[0]) < 0)
		free_perror_exit("close", e_path, NULL);
}
