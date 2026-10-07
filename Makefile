CC := gcc
CFLAGS := -Wall -Wextra -Werror -Wpedantic -Wunused-result \
          -O2 -D_FORTIFY_SOURCE=2

LESSON := $(word 2,$(MAKECMDGOALS))
TASK := $(word 3,$(MAKECMDGOALS))

DIR := $(firstword $(wildcard tasks/$(LESSON)* tasks/0$(LESSON)*))
SRC := $(firstword $(wildcard $(DIR)/$(TASK)_*.c $(DIR)/$(TASK).c))

BIN := /tmp/c_task
TEST_BIN := /tmp/c_task_test

.PHONY: help run test format

help:
	@echo "make run <lesson> <task>"
	@echo "make test <lesson> <task>"
	@echo "make format <lesson> <task>"

run:
	@test -n "$(DIR)" || (echo "Lesson $(LESSON) not found"; exit 1)
	@test -n "$(SRC)" || (echo "Task $(TASK) not found in $(DIR)"; exit 1)
	@echo "Running $(SRC)"
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)
	$(BIN)

test:
	@test -n "$(DIR)" || (echo "Lesson $(LESSON) not found"; exit 1)
	@test -n "$(SRC)" || (echo "Task $(TASK) not found in $(DIR)"; exit 1)
	@echo "Testing $(SRC)"
	$(CC) $(CFLAGS) -DTEST $(SRC) -o $(TEST_BIN)
	$(TEST_BIN)

format:
	@test -n "$(SRC)" || (echo "Task $(TASK) not found in $(DIR)"; exit 1)
	clang-format -i $(SRC)

%:
	@:
