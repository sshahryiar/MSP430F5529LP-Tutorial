#include "driverlib.h"


void GPIO_init(void);


void main(void)
{
    WDT_A_hold(WDT_A_BASE);

    GPIO_init();

    while(1)
    {
        if(GPIO_getInputPinValue(GPIO_PORT_P1,
                                 GPIO_PIN1) == 0)
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P4,
                                    GPIO_PIN7);

            GPIO_setOutputLowOnPin(GPIO_PORT_P1,
                                   GPIO_PIN0);
        }

        if(GPIO_getInputPinValue(GPIO_PORT_P2,
                                 GPIO_PIN1) == 0)
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P1,
                                    GPIO_PIN0);

            GPIO_setOutputLowOnPin(GPIO_PORT_P4,
                                   GPIO_PIN7);
        }
    };
}


void GPIO_init(void)
{
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,
                                         GPIO_PIN1);

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2,
                                         GPIO_PIN1);

    GPIO_setAsOutputPin(GPIO_PORT_P1,
                        GPIO_PIN0);

    GPIO_setDriveStrength(GPIO_PORT_P1,
                          GPIO_PIN0,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);

    GPIO_setAsOutputPin(GPIO_PORT_P4,
                        GPIO_PIN7);

    GPIO_setDriveStrength(GPIO_PORT_P4,
                          GPIO_PIN7,
                          GPIO_FULL_OUTPUT_DRIVE_STRENGTH);
}
