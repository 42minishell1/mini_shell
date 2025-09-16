/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:05:24 by jaehlee           #+#    #+#             */
/*   Updated: 2025/09/16 15:05:24 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISEHLL_H


# include "libft.h"
# include <stdio.h>  // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> // fork, execve, access, dup2, pipe, chdir, getcwd, isatty
# include <string.h> // strerror, strcmp, strtok 등
# include <errno.h>  // errno, 에러 처리
# include <fcntl.h>	 // open, O_RDONLY, O_WRONLY, O_CREAT, O_APPEND
# include <dirent.h> // opendir, readdir, closedir
# include <sys/types.h> // pid_t, stat 구조체
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/wait.h>  // wait, waitpid
# include <signal.h>    // signal, sigaction, kill
# include <termios.h>   // tcsetattr, tcgetattr (터미널 제어)
# include <sys/ioctl.h> // ioctl, ttyname, ttyslot
# include <readline/readline.h>   // readline
# include <readline/history.h>    // add_history, clear_history

// filename == NULL이면 none_file이다.
// filetype in:0 out:1
// here_doc normal: 0(꺽쇠 하나), here_doc:1 (꺽쇠 둘)
typedef struct s_file
{
	char	*filename;
	int		filetype;
	int		here_doc;
}	t_file;

typedef struct s_pipe
{
	t_file	infile;
	t_file	outfile;
	char	**cmd;
	s_pipe	*next;
}	t_pipe;


#endif