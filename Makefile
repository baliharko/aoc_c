.DEFAULT_GOAL := all

CC := clang
CFLAGS := -g -fsanitize=address -Wall -Wextra -std=c99 -I./util

DAY :=
DIR := $(shell dirname "$(DAY)" | sed 's/\/p.*//')
PART := $(shell echo $(DAY) | sed 's $(DIR)/  ')

SRCS := $(wildcard $(DAY).c) $(wildcard $(DIR)/common.c) $(filter-out %.h, $(wildcard util/*.c))
OBJS := $(patsubst %.c,%.o,$(SRCS))

all: compile link run clean

compile: $(OBJS)

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

link: $(PART)

$(PART): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@

run: $(PART)
	@time ./$(PART)

clean:
	@rm -f $(PART) $(OBJS) $(wildcard $(DIR)/common.o)

