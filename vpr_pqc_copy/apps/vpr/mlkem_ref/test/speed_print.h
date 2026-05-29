#ifndef PRINT_SPEED_H
#define PRINT_SPEED_H

#include <stddef.h>
#include <stdint.h>

int print_results(const char *s, uint64_t *t, size_t tlen);

void print_calls(const char *s, int t, size_t tlen);

void print_cycles(const char *s, int t, size_t tlen);
#endif
