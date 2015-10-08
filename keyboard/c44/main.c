#include "lufa.h"
#include "keyboard.h"
#include "wait.h"
#include "c44-util.h"

// slave version of matix scan, defined in matrix.c
void matrix_slave_scan(void);

int main(void)  __attribute__ ((weak));
int main(void)
{
    setup_hardware();
    setup_set_handedness();
    sei();

    /* wait for USB startup to get ready for debug output */
    uint8_t timeout = 200;  // timeout when USB is not available
    while (timeout-- && USB_DeviceState != DEVICE_STATE_Configured) {
        wait_ms(5);
#if defined(INTERRUPT_CONTROL_ENDPOINT)
        ;
#else
        USB_USBTask();
#endif
    }

    /* if (USB_DeviceState != DEVICE_STATE_Configured) { */
    if (!has_usb()) {
        // USB failed to connect, so run this device in slave mode.
        matrix_init();
        serial_slave_init();

        while (1) {
            matrix_slave_scan();
        }
    }

    /* init modules */
    keyboard_init();
    host_set_driver(&lufa_driver);

#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

    while (1) {
        keyboard_task();

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        USB_USBTask();
#endif
    }
}
