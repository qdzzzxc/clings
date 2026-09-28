CC := gcc
CFLAGS := -Wall -Wextra -Werror -Wpedantic -Wunused-result \
          -O2 -D_FORTIFY_SOURCE=2

LESSON := $(word 2,$(MAKECMDGOALS))
TASK := $(word 3,$(MAKECMDGOALS))

SRC := tasks/lesson_$(LESSON)/task_$(TASK).c
BIN := /tmp/c_task

.PHONY: help run format

help:
	@echo "make run <lesson> <task>"
	@echo "make format <lesson> <task>"

run:
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)
	$(BIN)

format:
	clang-format -i $(SRC)

%:
	@:
