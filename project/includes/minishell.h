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

# define HEREDOC_TEMPLATE "/tmp/minishell_hdXXXXXX"
# define PIPE_LIMIT 256
# define PIPE_RESET(fd) do { (fd)[0] = -1; (fd)[1] = -1; } while (0)
# define IS_ISOLATED_BUILTIN(n, prev) \
	(is_builtin((n)->cmd) && !(n)->next && (prev) == -1)

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
	t_file			*infile;
	t_file			*outfile;
	char			**cmd;
	t_heredoc		*herelist;
	struct s_pipe	*next;
	int				fd;
}	t_pipe;

typedef enum e_parse_status
{
	PARSE_ALLOC_ERROR = -1,
	PARSE_OK = 0,
	PARSE_SYNTAX_ERROR = 1
}	t_parse_status;

typedef struct s_shell
{
	char	**envp;
	int		last_status;
	int		stdin_backup;
	int		stdout_backup;
}	t_shell;


/*utils*/
void	free_token(void *content);
int		is_word_char(char c);
int		is_space(int c);
int		is_op1(char c);
/*parsing*/
int		push_tok(t_list **list, t_toktype type, char *value);
int		tokenize_metachar(t_list **list, char *line, int i);
int		tokenize_word(t_list **tokens, char *line, int i);
t_list	*lexer(char *line);
t_pipe	*pipe_new(void);
int		set_file(t_file **slot, const char *filename, t_ftype type, int quoted);
int		append_heredoc_node(t_pipe *pipe, const char *delimiter, int quoted);
int		parse_segment(t_pipe *pipe, t_list **cursor);
int		build_pipeline(t_list *tokens, t_pipe **out);
int		append_word(char ***array, const char *word);
void	free_str_array(char **array);
int		parse_line(char *line, t_pipe **pipeline);
void	free_pipeline(t_pipe *pipeline);

void	prompt(t_shell *shell);

int		execute_pipeline(t_shell *shell, t_pipe *pipeline);

void	destroy_shell(t_shell *shell);
void	init_shell(t_shell *shell, char **envp);

void	cleanup_heredocs(t_pipe *pipeline);
int		prepare_heredocs(t_shell *shell, t_pipe *pipeline);
int		process_single_heredoc(t_shell *shell, t_pipe *pipe, t_heredoc *hd);
int		write_heredoc_body(const char *delimit, int quoted, int fd);

void	close_redir(t_pipe *node);
int		open_redir(t_pipe *node);
int		wait_pipeline(pid_t *pids, int count, t_shell *shell);
void	pipeline_child_process(t_shell *shell, t_pipe *node,
			int prev_fd, int pipefd[2]);
void	pipeline_parent_after_fork(int *prev_fd, int pipefd[2]);

int		is_builtin(char **cmd);
int		run_builtin_parent(t_shell *shell, t_pipe *node);
int		run_builtin_child(t_shell *shell, t_pipe *node);
void	exec_external(t_shell *shell, t_pipe *node);
int		echo(t_pipe *tool);
int		cd(t_pipe *tool);
int		pwd(t_pipe *tool);
int		export(t_pipe *tool);
int		env_builtin(t_pipe *tool);
int		exit_builtin(t_pipe *tool);

#endif
