/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 22:22:59 by reira             #+#    #+#             */
/*   Updated: 2023/06/09 15:46:30 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	first_child(t_args args, int p[], char **e_path)
{
	get_fd(&args, 0, e_path);
	if (dup2(args.in_fd, STDIN_FILENO) < 0)
		free_perror_exit("dup2", e_path, NULL);
	if (close(args.in_fd) < 0)
		free_perror_exit("close", e_path, NULL);
	main_child(args, p, e_path);
}

void	main_child(t_args args, int p[], char **e_path)
{
	if (dup2(p[1], STDOUT_FILENO) < 0)
		free_perror_exit("dup2", e_path, NULL);
	if (close(p[0]) < 0)
		free_perror_exit("close", e_path, NULL);
	if (close(p[1]) < 0)
		free_perror_exit("close", e_path, NULL);
	get_cmdpath_exec(args, args.cmd_index, e_path);
}

void	last_child(t_args args, int p[], char **e_path)
{
	get_fd(&args, 1, e_path);
	if (dup2(p[1], STDOUT_FILENO) < 0)
		free_perror_exit("dup2", e_path, NULL);
	if (close(p[0]) < 0)
		free_perror_exit("close", e_path, NULL);
	if (close(p[1]) < 0)
		free_perror_exit("close", e_path, NULL);
	if (dup2(args.out_fd, STDOUT_FILENO) < 0)
		free_perror_exit("dup2", e_path, NULL);
	if (close(args.out_fd) < 0)
		free_perror_exit("close", e_path, NULL);
	get_cmdpath_exec(args, args.cmd_index, e_path);
}