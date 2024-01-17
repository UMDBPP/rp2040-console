#ifndef CONSOLE_H
#define CONSOLE_H

#include "../std-cmd/command.h"
#include "pico/stdlib.h"

#define BUF_SIZE 255

bool is_valid_char(char *c);
op_code get_command(command *cmd);

#endif