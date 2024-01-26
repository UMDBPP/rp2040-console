#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hardware/irq.h"
#include "hardware/uart.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "../../console.h"
#include "../../std-cmd/command.h"

#define GET_FLAG 42

command cmd = {0x00, NOP, {0, 0, 0, 0, 0, 0, 0}, NULL};

void help_handler(uint8_t *args);
void core1_entry(void);

int main() {
    stdio_init_all();

    sleep_ms(5000);

    printf("Multicore RP2040 Console Example - %s %s", __DATE__, __TIME__);

    multicore_launch_core1(core1_entry);

    help_handler(NULL);
    while (true) {
        get_command(&cmd);
        print_command(&cmd);
        cmd.handler(cmd.params);
    }
}

void get_handler(uint8_t *args) {
    multicore_fifo_push_blocking(GET_FLAG);
    uint32_t current = multicore_fifo_pop_blocking();

    printf("Current value from core 1 loop is %d\n", current);
}

void help_handler(uint8_t *args) {
    printf("Enter commands at the promp below\nCommand format: Op-Code args\n");
}

void core1_entry() {
    uint32_t current = 0;
    uint32_t flag = 0;

    while (true) {
        if (multicore_fifo_pop_timeout_us(100, &flag) && flag == GET_FLAG)
            multicore_fifo_push_blocking(current);
        current++;
    }
}

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
void set_handler(uint8_t *args) { printf("handler not implemented\n"); }