#include "driverlib.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_print.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"
#include "USB_API/USB_HID_API/UsbHid.h"


#include "hal.h"


#define LED_PORT            GPIO_PORT_P4
#define LED_PIN             GPIO_PIN7

#define MOUSE_PORT          GPIO_PORT_P6
#define MOUSE_UP_PIN        GPIO_PIN0
#define MOUSE_DOWN_PIN      GPIO_PIN1
#define MOUSE_LEFT_PIN      GPIO_PIN2
#define MOUSE_RIGHT_PIN     GPIO_PIN3
#define MOUSE_BUTTON_PIN    GPIO_PIN4

#define change_amount       1


typedef struct
{
    int8_t buttons;
    int8_t dX;
    int8_t dY;
    int8_t dZ;
}MOUSE_REPORT;


MOUSE_REPORT mouseReport = {0x00, 0x00, 0x00, 0x00};


void DIO_init(void);


void main (void)
{
    unsigned char t = 0x0000;

    WDT_A_hold(WDT_A_BASE);

    LCD_init();
    LCD_clear_home();

    LCD_goto(1, 0);
    LCD_putstr("MSP430 USB HID");

    LCD_goto(0, 1);
    LCD_putstr("X: ");

    LCD_goto(6, 1);
    LCD_putstr("Y:");

    LCD_goto(12, 1);
    LCD_putstr("B:");

    PMM_setVCore(PMM_CORE_LEVEL_2);
    USBHAL_initPorts();
    USBHAL_initClocks(8000000);
    USB_setup(TRUE, TRUE);

    DIO_init();

    __enable_interrupt();

    while (1)
    {
        if(GPIO_getInputPinValue(MOUSE_PORT,
                                 MOUSE_UP_PIN) == false)
        {
            mouseReport.dY += change_amount;
        }

        if(GPIO_getInputPinValue(MOUSE_PORT,
                                 MOUSE_DOWN_PIN) == false)
        {
            mouseReport.dY -= change_amount;
        }

        if(mouseReport.dY > 127)
        {
            mouseReport.dY = 127;
        }

        if(mouseReport.dY < -127)
        {
            mouseReport.dY = -127;
        }

        if(GPIO_getInputPinValue(MOUSE_PORT,
                                 MOUSE_LEFT_PIN) == false)
        {
            mouseReport.dX -= change_amount;
        }

        if(GPIO_getInputPinValue(MOUSE_PORT,
                                 MOUSE_RIGHT_PIN) == false)
        {
            mouseReport.dX += change_amount;
        }

        if(mouseReport.dX > 127)
        {
            mouseReport.dX = 127;
        }

        if(mouseReport.dX < -127)
        {
            mouseReport.dX = -127;
        }

        if(GPIO_getInputPinValue(MOUSE_PORT,
                                 MOUSE_BUTTON_PIN) == false)
        {
            mouseReport.buttons ^= 0x01;
        }

        switch (USB_getConnectionState())
        {
            case ST_ENUM_ACTIVE:
            {
                USBHID_sendReport((void *)&mouseReport,
                                  HID0_INTFNUM);

                print_C(2, 1, mouseReport.dX);
                print_C(8, 1, mouseReport.dY);
                print_C(14, 1, mouseReport.buttons);

                GPIO_toggleOutputOnPin(LED_PORT,
                                       LED_PIN);

                break;
            }

            case ST_PHYS_DISCONNECTED:
            case ST_ENUM_SUSPENDED:
            case ST_PHYS_CONNECTED_NOENUM_SUSP:
                break;

            case ST_ENUM_IN_PROGRESS:
            default:;
        }

        t++;
        if(t > 40)
        {
            t = 0;
            mouseReport.dX = 0;
            mouseReport.dY = 0;
            mouseReport.buttons = 0;
        }
    }
}


#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR (void)
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG ))
    {
        case SYSUNIV_NONE:
        {
            __no_operation();
            break;
        }

        case SYSUNIV_NMIIFG:
        {
            __no_operation();
            break;
        }

        case SYSUNIV_OFIFG:
        {
            UCS_clearFaultFlag(UCS_XT2OFFG);
            UCS_clearFaultFlag(UCS_DCOFFG);
            SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
            break;
        }

        case SYSUNIV_ACCVIFG:
        {
            __no_operation();
            break;
        }
        case SYSUNIV_BUSIFG:
        {
            SYSBERRIV = 0;
            USB_disable();
        }
    }
}


void DIO_init(void)
{
    GPIO_setAsInputPinWithPullUpResistor(MOUSE_PORT,
                                         MOUSE_UP_PIN);

    GPIO_setAsInputPinWithPullUpResistor(MOUSE_PORT,
                                         MOUSE_DOWN_PIN);

    GPIO_setAsInputPinWithPullUpResistor(MOUSE_PORT,
                                         MOUSE_LEFT_PIN);

    GPIO_setAsInputPinWithPullUpResistor(MOUSE_PORT,
                                         MOUSE_RIGHT_PIN);

    GPIO_setAsInputPinWithPullUpResistor(MOUSE_PORT,
                                         MOUSE_BUTTON_PIN);
}
