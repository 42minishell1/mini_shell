# Minishell
## 코드 읽기 순서
1) 엔트리/루프 (`project/src/minishell/core/`)  
   - `core/main.c`: `init_shell` → `prompt` → `destroy_shell` 전체 흐름.  
   - `core/prompt.c`: `readline` 루프, `parse_line` → `execute_pipeline`. 시그널 결과를 `last_status`에 반영.  
   - `core/shell_state.c`, `core/signals.c`: 환경/FD 백업, 부모/자식 시그널 설정.
2) 파싱 (`project/src/minishell/parsing/`)  
   - 토큰화: `parsing/lexer/lexer.c`, `lexer_tokens.c`, `lexer_utils.c`.  
   - 구문 트리화: `parsing/parser/parser.c` → `parser_segment.c`(+`parser_segment_utils.c`)에서 `t_pipe` 노드 구성, heredoc 큐 적재.  
   - 확장: `parsing/expansion/expansion_*.c`에서 `$` 확장, 따옴표, 공백 분리.  
   - 기타: `parser_redir.c`, `parser_nodes.c`, `parser_cleanup.c`에서 리다이렉션 노드 생성/해제.
3) 실행 (`project/src/minishell/execution/`)  
   - 파이프라인: `execution/pipeline/exec_pipeline.c`(heredoc 준비 → fork/pipe), `exec_pipeline_child.c`, `exec_utils.c`, `exec_wait.c`.  
   - 외부 명령: `execution/external/exec_external.c`에서 PATH 검색, 접근성 검사, `execve`.  
   - 빌트인: `execution/builtins/builtin.c` 분기와 `echo.c`, `cd.c`, `pwd.c`, `export.c`, `env.c`, `unset.c`, `exit.c`.  
   - 리다이렉션/heredoc: `execution/redirects/redir*.c`, `heredoc*.c`.  
   - 환경 유틸: `execution/env/env_utils.c`.
4) 공용 헤더  
   - `project/includes/minishell.h`에서 구조체(`t_tok`, `t_file`, `t_heredoc`, `t_pipe`, `t_shell`)와 전역 상수를 먼저 확인한다.

## 주요 기능 스냅샷
- 빌트인: `echo`, `cd`, `pwd`, `export`, `env`, `unset`, `exit`
- 파이프(`|`), 리다이렉션(`<`, `>`, `>>`, `<<`), heredoc(따옴표 유무에 따라 확장/리터럴)
- 환경변수 확장 및 따옴표/공백 분리
- `readline` 프롬프트(`shell : `), 히스토리, `SIGINT` 처리(Ctrl+C 시 현재 줄 취소, `SIGQUIT` 무시)

## 개발 팁/제한
- 최대 파이프 개수는 `PIPE_LIMIT`(256)으로 제한된다.
- 실행 전 `make fclean && make`로 정리 빌드를 하면 오래된 산출물 섞임을 막는다.
- 문제 발생 시 `./minishell` 실행 전에 `leaks`, `valgrind` 등으로 메모리/FD 누수 여부를 확인한다.
