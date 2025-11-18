/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:39:08 by jaemyu            #+#    #+#             */
/*   Updated: 2025/09/17 15:39:08 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export VARIABLE_NAME=value
// VARIABLE_NAME은 환경변수의 이름, value는 해당 변수에 할당하고자 하는 값
// 새로운 MY_VAR 환경 변수를 생성하고 이에 값을 할당하려면
// export MY_VAR="Hello World"
// echo $MY_VAR = Hello World
// export PATH="$PATH:/my/custom/path" 기존의 환경변수에 새로운 경로를 추가
// 변수가 아닌 $PATH 문자열을 사용하려면 ""가 아닌 ''
// export -p 옵션을 사용하면 현재 쉘에 설정된 모든 환경변수 출력 가능
// 환경변수를 사용하지 않아도 쉘의 일반 변수를 선언할 수 있다.
// export ENV_HELLO="world" = HELLO="world"
// $ 문자열로 변수 참조 가능
// echo $ENV_HELLO = world

int	export(t_pipe *tool)
{
	(void)tool;
	return (0);
}
