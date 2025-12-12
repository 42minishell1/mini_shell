# Minishell
## 주요 기능
- `echo`, `cd`, `pwd`, `export`, `env`, `unset`, `exit` 빌트인 지원
- 파이프(`|`)와 리다이렉션(`<`, `>`, `>>`, `<<`) 처리, heredoc 확장(따옴표 유무에 따른 확장/리터럴 모드)
- 환경변수 확장 및 따옴표/공백 분리 로직
- `readline` 기반 프롬프트(`shell : `)와 히스토리 저장
- `SIGINT`(Ctrl+C) 처리: 프롬프트 초기화 후 계속 입력, `SIGQUIT` 무시

## 빌드
필수 의존성: `readline`(+`ncurses`), `make`, C 컴파일러.
```bash
make          # 루트 Makefile로 libft와 minishell 라이브러리를 빌드 후 실행파일 생성
```
빌드 산출물: `minishell`(실행파일), `project/library` 아래 정적 라이브러리 캐시.

## 실행 및 사용
```bash
./minishell
```
- 프롬프트는 `shell : ` 형태다.
- 파이프/리다이렉션/환경변수(`$VAR`, `$?`)를 포함한 명령을 입력할 수 있다.
- heredoc 구분자를 따옴표로 감싸면(예: `'EOF'`) 변수 확장을 하지 않는다.
- Ctrl+C: 현재 입력 줄을 취소하고 새 프롬프트로 복귀.  
  Ctrl+D: 입력 종료(EOF) 시 `exit`와 함께 종료.

## 디렉토리 구조(요약)
- `Makefile` : 루트 빌드 스크립트
- `project/includes/` : 공용 헤더(`minishell.h`)
- `project/src/minishell/` : 핵심 소스
  - `parsing/` : 토큰화, 파싱, 확장, heredoc 준비
  - `execution/` : 빌트인/외부 명령 실행, 파이프라인, 리다이렉션
  - `utils/` : 셸 상태, 시그널, 공용 도우미
- `project/src/libft/` : libft 라이브러리
- `project/library/` : 빌드된 정적 라이브러리 출력 위치

## 개발 팁
- 최대 파이프 개수는 `PIPE_LIMIT`(256)으로 제한된다.
- 실행 전 `make fclean && make`로 정리 빌드를 하면 오래된 산출물 섞임을 막는다.
- 문제 발생 시 `./minishell` 실행 전에 `leaks`, `valgrind` 등으로 메모리/FD 누수 여부를 확인한다.
