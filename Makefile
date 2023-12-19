.DEFAULT_GOAL := all

CC := gcc
CFLAGS := -Wall -Wextra -std=c99

DAY :=
DIR := $(shell dirname "$(DAY)" | sed 's/\/p.*//')
PART:=$(shell echo $(DAY) | sed 's $(DIR)/  ')

all : compile link run clean

compile:
	@$(CC) $(CFLAGS) -c $(DAY).c $(wildcard $(DIR)/common.c)

link:
	@$(CC) $(CFLAGS) $(PART).o $(wildcard common.o) -o $(PART)

run:
	@./$(PART)
	
clean:
	@rm $(PART) $(PART).o $(wildcard $(shell fd 'common.o' .))

