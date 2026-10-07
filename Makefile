CC := gcc
CFLAGS := -Wall -Wextra -Werror -Wpedantic -Wunused-result -O2 -D_FORTIFY_SOURCE=2
export CC CFLAGS
.DEFAULT_GOAL := help
COMMAND := $(firstword $(MAKECMDGOALS))
ARGS := $(wordlist 2,99,$(MAKECMDGOALS))
.PHONY: help run test format reset reset-all save check stats
help run test format reset reset-all save check stats:
	@sh scripts/exercises.sh $@ $(ARGS)
# Numeric goals are arguments; unknown command names remain errors.
ifneq ($(filter $(COMMAND),run test format reset save check stats),)
$(foreach arg,$(ARGS),$(if $(shell printf '%s' '$(arg)' | LC_ALL=C tr -d '0-9'),,$(eval .PHONY: $(arg))$(eval $(arg):;@:)))
endif
