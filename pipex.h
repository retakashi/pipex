/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:45:51 by reira             #+#    #+#             */
/*   Updated: 2023/06/12 20:15:44 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define PATH_LEN 5 //PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
# define HERE_DOC_LEN 9
# define TRUE 0
# define FALSE 1

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**envp;
	int		cmd_index;
	int		cmd_cnt;
	int		cmd_total;
	int		in_fd;
	int		out_fd;
}			t_args;

typedef struct s_path
{
	size_t	i;
	char	**argv_cmd;
	char	*path;
	char	*cmd_path;
}			t_path;

typedef struct s_heredoc
{
	size_t	limit_len;
	char	*line;
	int		flg;
}			t_heredoc;

//pipex_utils.c
int			close_fd(int fd1, int fd2, int fd3, int fd4);
char		**get_envp_path(char **envp);
void		get_cmdpath_exec(t_args args, int cmd, char **e_path);
t_args		args_init(int argc, char **argv, char **envp);
//bonus_utils.c
void		get_fd(t_args *args, int flg, char **e_path);
void		first_child(t_args args, int p[], char **e_path);
void		main_child(t_args args, int p[], char **e_path);
void		last_child(t_args args, int p[], char **e_path);
//free_perror_exit.c
char		*ft_free(char **str);
void		free_perror_exit(char *str, char **free1, char **free2);
void		free_put_error_exit(char **str, char **free);
//heredoc.c
void		do_heredoc(t_args args, char **e_path);
void		child_heredoc(t_args args, int p[], char **e_path);
void		parent_heredoc(int p[], char **e_path);

#endif
