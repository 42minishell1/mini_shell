/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:39:08 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/19 12:10:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 환경변수 키가 유효한 식별자인지 검사한다.
static int	is_valid_key(char *s)
{
	int	i;

	if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

// export 출력 형식에 맞춰 환경변수 목록을 표시한다.
static int	print_export_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

// 인자로 받은 key=value를 파싱해 환경변수에 반영한다.
static int	handle_arg(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;
	int		ret;

	if (!is_valid_key(arg))
		return (ft_putendl_fd("minishell: export: not a valid identifier",
				STDERR_FILENO), 1);
	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	key = ft_substr(arg, 0, eq - arg);
	if (!key)
		return (1);
	ret = env_set(&shell->envp, key, eq + 1);
	free(key);
	return (ret);
}

// export 빌트인: 인자가 없으면 목록을 출력하고, 있으면 설정한다.
int	export(t_shell *shell, t_pipe *tool)
{
	int	i;
	int	status;

	if (!tool->cmd || !tool->cmd[0])
		return (0);
	if (!tool->cmd[1])
		return (print_export_env(shell->envp));
	i = 1;
	status = 0;
	while (tool->cmd[i])
	{
		if (handle_arg(shell, tool->cmd[i]))
			status = 1;
		i++;
	}
	return (status);
}
