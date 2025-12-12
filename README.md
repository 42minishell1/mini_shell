Minishell

작은 쉘 구현체다. C 코드를 읽는 사람이 흐름을 빠르게 따라가도록, 어떤 파일부터 보면 되는지 안내한다.

## 코드 읽기 순서
1) `project/src/minishell/main.c`  
   - `init_shell` → `prompt` → `destroy_shell` 흐름을 잡는다. `t_shell` 필드가 어떤 역할인지 본다.
2) `project/src/minishell/prompt.c`  
   - `readline` 루프, `parse_line` 호출, 성공 시 `execute_pipeline`. 시그널 처리 결과가 `last_status`에 반영되는 부분을 확인한다.
3) 파싱 단계  
   - 토큰화: `parsing/lexer.c`, `lexer_tokens.c`, `lexer_utils.c`에서 입력을 토큰 리스트로 만든다.  
   - 구문 트리화: `parsing/parser.c` → `parser_segment.c`(+`parser_segment_utils.c`)에서 `t_pipe` 노드를 채운다. heredoc은 여기서 큐에 쌓인다.  
   - 확장: `parsing/expansion_*.c`에서 `$` 확장, 따옴표, 공백 분리를 처리한다.  
   - 보조: `parser_redir.c`, `parser_nodes.c`, `parser_cleanup.c`에서 리다이렉션 노드 생성/해제 로직을 본다.
4) 실행 단계  
   - 파이프라인 오케스트레이션: `execution/exec_pipeline.c`(heredoc 준비 → fork/pipe 루프).  
   - 자식 쪽: `exec_pipeline_child.c`에서 FD 연결 후 빌트인/외부 명령으로 분기.  
   - 외부 명령: `exec_external.c`에서 PATH 검색, 접근성 검사, `execve` 호출.  
   - 부모 빌트인/대기: `exec_utils.c`, `exec_wait.c`에서 단독 빌트인 처리와 종료 코드 수집.  
   - 빌트인 구현: `execution/builtin.c` 분기와 `echo.c`, `cd.c`, `pwd.c`, `export.c`, `env.c`, `unset.c`, `exit.c`.  
   - 리다이렉션·heredoc 도우미: `execution/redir*.c`, `heredoc*.c`.
5) 공용/헤더  
   - `utils/shell_state.c`(초기화/해제), `utils/signals.c`(시그널).  
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
