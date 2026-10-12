CC := gcc
CFLAGS := -Wall -Wextra -Werror -Wpedantic -Wunused-result -g -O1 -D_FORTIFY_SOURCE=2 -fsanitize=address,undefined -fno-sanitize-recover=all
export CC CFLAGS
.DEFAULT_GOAL := help
COMMAND := $(firstword $(MAKECMDGOALS))
ARGS := $(wordlist 2,99,$(MAKECMDGOALS))
.PHONY: help run test format reset check stats
help run test format reset check stats:
	@sh scripts/exercises.sh $@ $(ARGS)
# Numbers and track names (exercises/<name>) are arguments; unknown command names remain errors.
ifneq ($(filter $(COMMAND),run test format reset check stats),)
$(foreach arg,$(ARGS),$(if $(or $(if $(shell printf '%s' '$(arg)' | LC_ALL=C tr -d '0-9'),,1),$(wildcard exercises/$(arg)/.)),$(eval .PHONY: $(arg))$(eval $(arg):;@:)))
endif
