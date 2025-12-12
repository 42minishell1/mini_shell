/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:30:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/20 10:30:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

// Ctrl+C를 누르면 프롬프트 줄을 새로 갱신하고 상태 코드를 남긴다.
static void	handle_sigint(int signo)
{
	(void)signo;
	g_last_signal = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// 부모 프로세스용 시그널 핸들러를 설치한다.
void	setup_parent_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

// 자식 프로세스에서는 기본 시그널 동작을 사용한다.
void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
