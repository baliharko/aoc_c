.DEFAULT_GOAL := all

CC := clang
CFLAGS := -g -fsanitize=address -Wall -Wextra -std=c99 -I./util

DAY ?=
DIR := $(shell dirname "$(DAY)" | sed 's/\/p.*//')
PART := $(shell echo $(DAY) | sed 's $(DIR)/  ')
YEAR ?=

SRCS := $(wildcard $(DAY).c) $(wildcard $(DIR)/common.c) $(filter-out %.h, $(wildcard util/*.c))
OBJS := $(patsubst %.c,%.o,$(SRCS))

OUTPUT := aoc

.PHONY: all compile link run clean run_year

all: compile link run clean

compile: $(OBJS)

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

link: $(OUTPUT)

$(OUTPUT): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@

run: $(OUTPUT)
	@env MallocNanoZone=0 time ./$(OUTPUT)

clean:
	@rm -f $(OUTPUT) $(OBJS) $(wildcard $(DIR)/common.o)

run_year:
	@if [ -z "$(YEAR)" ]; then \
		echo "Error: Please provide a year parameter. Usage: make run_year YEAR=YYYY"; \
		exit 1; \
	fi
	@if [ ! -d "$(YEAR)" ]; then \
		echo "Error: Directory $(YEAR) does not exist"; \
		exit 1; \
	fi
	@for i in $$(ls $(YEAR)); do \
		echo "Day $$i"; \
		for j in 1 2; do \
			echo "Part $$j"; \
			$(MAKE) DAY=$(YEAR)/$$i/p$$j || true; \
		done; \
	done
