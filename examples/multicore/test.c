#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../console.h"
#include "../../std-cmd/command.h"
#include "hardware/irq.h"
#include "hardware/uart.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "pico/util/queue.h"

#define GET_FLAG 42
#define FIFO_LENGTH 32

command cmd = {0x00, NOP, {0, 0, 0, 0, 0, 0, 0}, NULL};

queue_t zero_one_queue;
queue_t one_zero_queue;

void help_handler(uint8_t *args);
void core1_entry(void);

int main() {
    stdio_init_all();

    set_sys_clock_48mhz();

    sleep_ms(5000);

    queue_init(&zero_one_queue, 4, FIFO_LENGTH);
    queue_init(&one_zero_queue, 4, FIFO_LENGTH);

    printf("Multicore RP2040 Console Example - %s %s\n", __DATE__, __TIME__);

    multicore_launch_core1(core1_entry);

    help_handler(NULL);
    while (true) {
        get_command(&cmd);
        print_command(&cmd);
        cmd.handler(cmd.params);
    }
}

void get_handler(uint8_t *args) {
    uint32_t data = GET_FLAG;
    uint32_t current = 0;
    queue_add_blocking(&zero_one_queue, &data);
    queue_remove_blocking(&one_zero_queue, &current);

    printf("Current value from core 1 loop is %d\n", current);
}

void help_handler(uint8_t *args) {
    printf("Enter commands at the promp below\nCommand format: Op-Code args\n");
}

void core1_entry() {
    uint32_t current = 0;
    uint32_t flag = 0;

    while (true) {
        if (!queue_is_empty(&zero_one_queue)) {
            queue_remove_blocking(&zero_one_queue, &flag);

            if (flag == GET_FLAG) queue_add_blocking(&one_zero_queue, &current);
        }

        current++;
        sleep_us(100);
        tight_loop_contents();
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