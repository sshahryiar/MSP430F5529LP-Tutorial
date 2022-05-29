#include "MAX6675.h"


void SPI_DIO_init(void)
{
    GPIO_setAsPeripheralModuleFunctionInputPin(MISO_port, MISO_pin);

    GPIO_setAsPeripheralModuleFunctionOutputPin(MOSI_port, MOSI_pin);
    GPIO_setAsPeripheralModuleFunctionOutputPin(CLK_port, CLK_pin);

    GPIO_setAsOutputPin(CS_port, CS_pin);
    GPIO_setDriveStrength(CS_port, CS_pin, GPIO_FULL_OUTPUT_DRIVE_STRENGTH);
}


void USCI_SPI_init(void)
{
    USCI_A_SPI_initMasterParam SPI_param = {0};

    SPI_DIO_init();

    SPI_param.selectClockSource = USCI_A_SPI_CLOCKSOURCE_SMCLK;
    SPI_param.clockSourceFrequency = UCS_getSMCLK();
    SPI_param.desiredSpiClock = 1000000;
    SPI_param.msbFirst = USCI_A_SPI_MSB_FIRST;
    SPI_param.clockPhase = USCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
    SPI_param.clockPolarity = USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW;

    USCI_A_SPI_initMaster(USCI_A0_BASE, &SPI_param);

    USCI_A_SPI_enable(USCI_A0_BASE);
}


void MAX6675_init(void)
{
    USCI_SPI_init();
}


unsigned char MAX6675_get_ADC(unsigned int *ADC_data)
{
	unsigned char lb = 0;
	unsigned char hb = 0;
	unsigned char samples = no_of_samples;
	unsigned int temp_data = 0;
	unsigned long avg_value = 0;


	while(samples > 0)
	{
	    CS_pin_low();
			
	    USCI_A_SPI_transmitData(USCI_A0_BASE, 0x00);
	    while(USCI_A_SPI_isBusy(USCI_A0_BASE));
		hb = USCI_A_SPI_receiveData(USCI_A0_BASE);
		while(USCI_A_SPI_isBusy(USCI_A0_BASE));

		USCI_B_SPI_transmitData(USCI_A0_BASE, 0x00);
        while(USCI_A_SPI_isBusy(USCI_A0_BASE));
        lb = USCI_A_SPI_receiveData(USCI_A0_BASE);
        while(USCI_A_SPI_isBusy(USCI_A0_BASE));

		 CS_pin_high();
		 
		 temp_data = hb;
		 temp_data <<= 8;
		 temp_data |= lb;
		 temp_data &= 0x7FFF;
		 
		 avg_value += (unsigned long)temp_data;
		 
		 samples--;
		 delay_ms(10);
	};

	temp_data = (avg_value >> 4);

	if((temp_data & 0x04) == close_contact)
	{
		*ADC_data = (temp_data >> 3);
		return close_contact;
	}
	else
	{
		*ADC_data = (count_max + 1);
		return open_contact;
	}
}


float MAX6675_get_T(unsigned int ADC_value, unsigned char T_unit)
{
	float tmp = 0.0;

	tmp = (((float)ADC_value) * scalar_deg_C);

	switch(T_unit)
	{
		case deg_F:
		{
			 tmp *= scalar_deg_F_1;
			 tmp += scalar_deg_F_2;
			 break;
		}
		case tmp_K:
		{
			tmp += scalar_tmp_K;
			break;
		}
		default:
		{
			break;
		}
	}

	return tmp;
}
