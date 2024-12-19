#pragma once

#include <stdio.h>

int count_lines(FILE* file);

// Returns index of first occurence, else -1
int indexof(const char* haystack, const char* needle);

int is_digit(const char c);

char **tokens(char *str, const char *delimiter);

int countToks(const char *line);

char* strReplace(char *str, const char *search, const char *replace);
