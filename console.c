#include "console.h"

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
bool __not_in_flash_func(is_valid_char)(char *c) {
    switch (*c) {
        case 32 ... 126:
        case 8:
        case 127:
        case 10:
            return true;
        default:
            return false;
    }
}

op_code __not_in_flash_func(get_command)(command *cmd) {
    current = 0;

    printf("\n" PROMPT "$ ");

    do {
        // time1 = get_absolute_time();
        curr_char = getchar_timeout_us(0);

        if (is_valid_char(&curr_char)) {
            putchar_raw(curr_char);
            // time2 = get_absolute_time();

            // printf("\n\ndelay from receive to print %ld\n\n",
            //        absolute_time_diff_us(time1, time2));

            buf[current] = curr_char;

            switch (curr_char) {
                case 8:
                case 127:
                    if (current > 0) current--;
                    break;
                default:
                    current++;
            }
        }

    } while (curr_char != 0x0A);

    buf[current] = 0;

    parse_text_command(buf, cmd, false);

    return cmd->op;
}

// void callback(void *ptr) {
//     int *i = (int *)ptr;  // cast void pointer back to int pointer
//     // read the character which caused to callback (and in the future read
//     the
//     // whole string)
//     *i = getchar_timeout_us(100);  // length of timeout does not affect
//     results
// }