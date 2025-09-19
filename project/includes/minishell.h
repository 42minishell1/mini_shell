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
# define MINISHELL_H


# include "libft.h"
# include <stdio.h>  // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> // fork, execve, access, dup2, pipe, chdir, getcwd, isatty
# include <string.h> // strerror
# include <errno.h>  // errno, 에러 처리
# include <fcntl.h>	 // open, O_RDONLY, O_WRONLY, O_CREAT, O_APPEND
# include <dirent.h> // opendir, readdir, closedir
# include <sys/types.h> // pid_t, stat 구조체
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/wait.h>  // wait, waitpid
# include <signal.h>    // signal, sigaction, kill
# include <termios.h>   // tcsetattr, tcgetattr (터미널 제어)
# include <sys/ioctl.h> // ioctl, ttyname, ttyslot
# include <readline/readline.h> // readline
# include <readline/history.h>  // add_history, clear_history

/*
	T_WORD,     일반 단어
	T_PIPE,     |
	T_LT,       <
	T_GT,       >
	T_DLT,      <<
	T_DGT       >>
*/
typedef enum e_toktype
{
	T_WORD,
	T_PIPE,
	T_LT,
	T_GT,
	T_DLT,
	T_DGT
}	t_toktype;

typedef struct s_tok
{
	char			*value;
	t_toktype		type;
	struct s_tok	*next;
}	t_tok;

/*	리다이렉션 종류 
	F_IN = 0,         <
	F_OUT_TRUNC = 1,  >
	F_OUT_APPEND = 2, >>
	F_HEREDOC = 3     << (delimiter 기반)
*/
typedef enum e_ftype
{
	F_IN = 0,
	F_OUT_TRUNC = 1,
	F_OUT_APPEND = 2,
	F_HEREDOC = 3
}	t_ftype;

/*
	filename == NULL이면 리다이렉션 없음(none_file)으로 간주함.
	F_HEREDOC일 때 filename은 'delimiter'를 의미함.
	quoted: heredoc에서 구분자가 따옴표로 감싸졌는지 여부 (0: 확장, 1: 리터럴)
*/
typedef struct s_file
{
	char	*filename;
	t_ftype	type;
	int		quoted;
}	t_file;

/*
	heredoc은 한 명령에서 여러 번 등장할 수 있음
	파싱 순서대로 모두 수집하기 위해 리스트로 보관
	delim: 종료 문자열(delimiter) 
	quoted: heredoc에서 구분자가 따옴표로 감싸졌는지 여부 (0: 확장, 1: 리터럴)
*/
typedef struct s_heredoc
{
	char				*delim;
	int					quoted;
	struct s_heredoc	*next;
}	t_heredoc;

/*
	파이프 라인의 한 명령을 표현
	infile/outfile : 마지막에 등장한 <, >, >>, << 만 최종 반영
	herelist      : 등장한 모든 << 를 순서대로 수집
	cmd           : NULL-종결 argv (cmd[0]이 명령)
	next          : 다음 파이프 요소
*/
typedef struct s_pipe
{
	t_file			infile;
	t_file			outfile;
	char			**cmd;
	t_heredoc		*herelist;
	struct s_pipe	*next;
	int				fd;
}	t_pipe;



/*utils*/
void	del_token_content(void *content);
int		is_word_char(char c);
int		is_space(int c);
int		is_op1(char c);
/*parsing*/
int		push_tok(t_list **list, t_toktype type, char *value);
int		tokenize_metachar(t_list **list, char *line, int i);
int		tokenize_word(t_list **tokens, char *line, int i);

void	prompt();

#endif