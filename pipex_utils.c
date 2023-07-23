/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 22:30:59 by reira             #+#    #+#             */
/*   Updated: 2023/06/24 17:07:50 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	get_fd(t_args *args, int flg, char **e_path)
{
	int	file;

	if (flg == 0)
	{
		file = 1;
		args->in_fd = open(args->argv[file], O_RDONLY);
		if (args->in_fd < 0)
			free_perror_exit(args->argv[1], e_path, NULL);
	}
	else
	{
		file = args->argc - 1;
		args->out_fd = open(args->argv[file], O_WRONLY | O_CREAT | O_TRUNC,
				S_IREAD | S_IWRITE);
		if (args->out_fd < 0)
			free_perror_exit(args->argv[args->argc - 1], e_path, NULL);
	}
}

char	**get_envp_path(char **envp)
{
	char	**e_path;
	size_t	i;

	i = 0;
	e_path = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	e_path = ft_split(envp[i], ':');
	if (e_path == NULL)
		free_perror_exit("malloc", NULL, NULL);
	ft_strlcpy(e_path[0], &e_path[0][5], ft_strlen(&e_path[0][5]) + 1);
	return (e_path);
}

void	get_cmdpath_exec(t_args args, int cmd, char **e_path)
{
	t_path	pa;

	pa.argv_cmd = ft_split(args.argv[cmd], ' ');
	if (pa.argv_cmd == NULL)
		free_perror_exit("malloc", e_path, NULL);
	pa.i = 0;
	while (e_path[pa.i++] != NULL)
	{
		pa.path = ft_strjoin(e_path[pa.i], "/");
		if (pa.path == NULL)
			free_perror_exit("malloc", e_path, pa.argv_cmd);
		pa.cmd_path = ft_strjoin(pa.path, pa.argv_cmd[0]);
		if (pa.cmd_path == NULL)
		{
			free(pa.path);
			free_perror_exit("malloc", e_path, pa.argv_cmd);
		}
		if (access(pa.cmd_path, X_OK) == 0 && execve(pa.cmd_path, pa.argv_cmd,
				args.envp) < 0)
			free_perror_exit("execve", e_path, pa.argv_cmd);
	}
	free(pa.path);
	free(pa.cmd_path);
	free_put_error_exit(pa.argv_cmd, e_path);
}

t_args	args_init(int argc, char **argv, char **envp)
{
	t_args	args;

	args.argc = argc;
	args.argv = argv;
	args.envp = envp;
	args.cmd_index = 2;
	args.cmd_cnt = 0;
	args.cmd_total = argc - 3;
	return (args);
}
