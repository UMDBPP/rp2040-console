#include "console.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pico/stdlib.h"
#include "../std-cmd/command.h"

static int chars_rxed = 0;

char buf[BUF_SIZE];
char curr_char = 0;
uint16_t current = 0;

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

    printf("\nRP2040$ ");

    do {
        curr_char = getchar_timeout_us(0);

        if (is_valid_char(&curr_char)) {
            putchar_raw(curr_char);

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

    parse_text_command(buf, cmd);

    return cmd->op;

    // chars_rxed = current - 1;

    // current = 0;

    // while (buf[current] != ' ') current++;

    // if (current = chars_rxed + 1)
    //     return NOP;
    // else
    //     buf[current] = 0;

    // if (strcmp(buf, echo_command_string) == 0)
    //     return TEXT;
    // else if (strcmp(buf, reset_command_string) == 0)
    //     return RESET;
    // else if (strcmp(buf, status_command_string) == 0)
    //     return STAT;
    // else
    //     return NOP;
}

// void callback(void *ptr) {
//     int *i = (int *)ptr;  // cast void pointer back to int pointer
//     // read the character which caused to callback (and in the future read
//     the
//     // whole string)
//     *i = getchar_timeout_us(100);  // length of timeout does not affect
//     results
// }

void no_op_handler(uint8_t *args) { printf("handler not implemented\n"); }
void test_handler(uint8_t *args) { printf("handler not implemented\n"); }
void text_handler(uint8_t *args) { printf("handler not implemented\n"); }
void vent_handler(uint8_t *args) { printf("handler not implemented\n"); }
void reset_handler(uint8_t *args) { printf("handler not implemented\n"); }
void pos_handler(uint8_t *args) { printf("handler not implemented\n"); }
void term_handler(uint8_t *args) { printf("handler not implemented\n"); }
void ack_handler(uint8_t *args) { printf("handler not implemented\n"); }
void nack_handler(uint8_t *args) { printf("handler not implemented\n"); }
void err_handler(uint8_t *args) { printf("handler not implemented\n"); }
void stat_handler(uint8_t *args) { printf("handler not implemented\n"); }
void get_handler(uint8_t *args) { printf("handler not implemented\n"); }
void set_handler(uint8_t *args) { printf("handler not implemented\n"); }