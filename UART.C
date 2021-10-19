/*******************************************************************************
 *
 *
 * Simple SmartFusion2 Microcontroller subsystem (MSS) GPIO example program.
 *
 *
 */
#include "drivers/mss_gpio/mss_gpio.h"
#include "CMSIS/system_m2sxxx.h"
#include "drivers/mss_uart/mss_uart.h"
#include <stdio.h>

/* Main function */


/*==============================================================================
 * main() function.
 */
#define RX_BUFF_SIZE 64
int main()
{
	uint8_t rx_buff[64];
	uint8_t rc[10];
	uint32_t rx_idx  = 0;
	uint32_t rx_size;
	uint32_t gpio_pattern;

	char data_memory[16] = "Data Memory";
	char inst_memory[16] = "Inst Memory";

	//Initialize Registers
	MSS_GPIO_config(MSS_GPIO_0, MSS_GPIO_OUTPUT_MODE);
	MSS_GPIO_config(MSS_GPIO_1, MSS_GPIO_OUTPUT_MODE);
	MSS_UART_init(&g_mss_uart0,MSS_UART_9600_BAUD,MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	
	//=========================================================================
	
	while(1){
	rx_size = MSS_UART_get_rx(&g_mss_uart0, rx_buff, sizeof(rx_buff));
	if (rx_size > 0){
		switch(rx_buff[0]){
		 case 'D':
			MSS_UART_polled_tx(&g_mss_uart0, data_memory, sizeof(data_memory));
			break;
		 case 'I':
			 MSS_UART_polled_tx(&g_mss_uart0, inst_memory, sizeof(inst_memory));
			 break;
		 case 'O':
			 gpio_pattern = MSS_GPIO_get_outputs();
			 gpio_pattern ^= 0xFFFFFFFF;
			 MSS_GPIO_set_outputs( gpio_pattern );
			 break;
		 default:
			 MSS_UART_polled_tx_string(&g_mss_uart0, "Nothing is happening");

		}// case statement

	  }// if statement


	}//while Loop
	 return(0);
}


