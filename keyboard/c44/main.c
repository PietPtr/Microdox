#include "lufa.h"
#include "keyboard.h"
#include "wait.h"
#include "c44-util.h"

void lufa_pre_setup(void) {
    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
}

int main(void)  __attribute__ ((weak));
int main(void)
{
    lufa_pre_setup();

    setup_hardware();

    if (!has_usb()) {
        keyboard_slave_loop();
    }

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


