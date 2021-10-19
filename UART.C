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

/* Function Declerations */
void uart0_rx_handler(mss_uart_instance_t *);


/*==============================================================================
 * main() function.
 */
uint8_t rx_buff[64];
uint32_t rx_size;
char data_memory[16] = "Data Memory";


int main()
{
	uint8_t rc[10];
	uint32_t rx_idx  = 0;
	uint32_t gpio_pattern;
	int a;



	//Initialize Registers
	MSS_GPIO_config(MSS_GPIO_0, MSS_GPIO_OUTPUT_MODE);
	MSS_GPIO_config(MSS_GPIO_1, MSS_GPIO_OUTPUT_MODE);
	MSS_UART_init(&g_mss_uart0,MSS_UART_9600_BAUD,MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	MSS_UART_set_rx_handler(&g_mss_uart0,uart0_rx_handler,MSS_UART_FIFO_SINGLE_BYTE);

	uart0_rx_handler(&g_mss_uart0);

	//=========================================================================


	 return(0);
}

void uart0_rx_handler(mss_uart_instance_t * this_uart)
   {
	char inst_memory[16] = "Inst Memory";
      uint32_t rx_idx  = 0;
      rx_size = MSS_UART_get_rx(this_uart, rx_buff, sizeof(rx_buff));
      if (rx_size > 0){
      MSS_UART_polled_tx(&g_mss_uart0, inst_memory, sizeof(inst_memory));
      }

   }
