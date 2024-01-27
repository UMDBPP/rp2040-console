#ifndef CONSOLE_H
#define CONSOLE_H

#include "pico/stdlib.h"
#include "std-cmd/command.h"

#define BUF_SIZE 255

#define PROMPT "RP2040"

// bool is_valid_char(char *c);
op_code get_command(command *);
void get_string(char *buf);

#endif