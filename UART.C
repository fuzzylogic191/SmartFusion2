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
	uint32_t rx_idx  = 0;
	uint32_t rx_size;
	char Test[10];
	int  Test1[10];
	char message[12] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
	int i;
	i = 0;

	//Initialize Registers

	MSS_UART_init(&g_mss_uart0,MSS_UART_9600_BAUD,MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);

	//=========================================================================
	while (1){
		rx_size = MSS_UART_get_rx(&g_mss_uart0, rx_buff, sizeof(rx_buff));
		if (rx_size > 0){
			Test[i] = rx_buff[0];

		if (Test[i] == '\r'){
			MSS_UART_polled_tx(&g_mss_uart0, Test, sizeof(Test));
			break;
			}//inner conditional statement
			i++;
		}//outer conditional statement
	}//loop


	 return(0);
}
