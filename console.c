#include "console.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pico/stdlib.h"
#include "std-cmd/command.h"

static int chars_rxed = 0;

char buf[BUF_SIZE];
char curr_char = 0;
uint16_t current = 0;
// absolute_time_t time1;
// absolute_time_t time2;

// Try to refactor to fast macro
// bool __not_in_flash_func(is_valid_char)(char *c) {
//     switch (*c) {
//         case 32 ... 126:
//         case 8:
//         case 127:
//         case 10:
//             return true;
//         default:
//             return false;
//     }
// }

op_code __not_in_flash_func(get_command)(command *cmd) {
    printf("\n" PROMPT "$ ");

    get_string(buf);

    parse_text_command(buf, cmd, false);

    return cmd->op;
}

void __not_in_flash_func(get_string)(char *string) {
    current = 0;

    do {
        curr_char = getchar_timeout_us(0);

        if (0 < curr_char && curr_char <= 0x7F) {
            if (isprint(curr_char) || isspace(curr_char) || '\r' == curr_char ||
                '\b' == curr_char || curr_char == 127) {
                if (current < BUF_SIZE) {
                    if (curr_char == 8 || curr_char == 127) {
                        if (current > 0) {
                            putchar_raw(curr_char);
                        }
                    } else {
                        putchar_raw(curr_char);
                    }
                }

                if (current < BUF_SIZE) {
                    string[current] = curr_char;

                    switch (curr_char) {
                        case 8:
                        case 127:
                            if (current > 0) current--;
                            break;
                        default:
                            current++;
                    }
                }
            }
        }

    } while (curr_char != 0x0A);

    string[current] = 0;
}

// void callback(void *ptr) {
//     int *i = (int *)ptr;  // cast void pointer back to int pointer
//     // read the character which caused to callback (and in the future read
//     the
//     // whole string)
//     *i = getchar_timeout_us(100);  // length of timeout does not affect
//     results
// }