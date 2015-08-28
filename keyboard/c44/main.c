#include <avr/io.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include "lufa.h"
#include "keyboard.h"
#include "keycode.h"
#include "action.h"
#include "action_util.h"
#include "wait.h"

static void setup_hardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
}

void matrix_slave_scan(void);

bool has_usb(void) {
   USBCON |= (1 << OTGPADE); //enables VBUS pad
   _delay_us(10);
   return (USBSTA & (1<<VBUS));  //checks state of VBUS
}

int main(void)  __attribute__ ((weak));
int main(void)
{
    setup_hardware();
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
