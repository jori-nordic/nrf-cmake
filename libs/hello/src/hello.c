#include <hello.h>
#include <nrf.h>

void hello_world_from_lib(int b) {
    (void)b++;
}

void start_radio(void) {
    NRF_RADIO_NS->TASKS_TXEN = 1;
    while(NRF_RADIO_NS->EVENTS_READY == 0) {}

    NRF_RADIO_NS->TASKS_START = 1;
}
