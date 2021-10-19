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

uint8_t rx_buff[64];
uint32_t rx_idx  = 0;
uint32_t rx_size;
char data_memory[16] = "Data Memory";
char inst_memory[16] = "Inst Memory";
#define FREQ 1e3

/* Function Decelerations */
void uart0_rx_handler(mss_uart_instance_t *);
void write_clk();
void write_rst();

/*Global Variables and definitions */


/*==============================================================================
 * main() function.
 */

int main()
{
	int size;

	//Initialize Registers

	MSS_UART_init(&g_mss_uart0,MSS_UART_9600_BAUD,MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);
	MSS_GPIO_init();
	//MSS_UART_set_loopback(&g_mss_uart0, MSS_UART_LOCAL_LOOPBACK_ON);

	//Create Vector Interrupt
	MSS_UART_set_rx_handler(&g_mss_uart0,uart0_rx_handler,MSS_UART_FIFO_SINGLE_BYTE);

	while (1){
	uart0_rx_handler(&g_mss_uart0);
	}
	//=========================================================================

	 return(0);
}

void uart0_rx_handler(mss_uart_instance_t * this_uart)
   {
	  int i;
	  i = 0;
      rx_size = MSS_UART_get_rx(this_uart, rx_buff, sizeof(rx_buff));

      if (rx_size > 0){

    	 switch(rx_buff[0])
    	 {
    	  	 case 'c':
    	  		 MSS_UART_polled_tx_string(&g_mss_uart0, "you have selected clock");
    	  		 //write_clk();
    	     break;
    	  	 case 'r':
    	  		 MSS_UART_polled_tx_string(&g_mss_uart0, "you have selected reset");
    	  		 write_rst();
    	  	 break;
    	  	 case 'o':
    	  		 MSS_UART_polled_tx_string(&g_mss_uart0, "writing output");
    	  	 break;
    	  	 default:
    	  		 printf('nothing');
    	  	break;
    	 }// switch statement


      }// if statement

   }//function statement

/* The function write_clk outputs a constant 1khz clock signal that will go from
 *  GPIO pin E5 of the smartfusion2 to the sys_clk_input signal of the J1
 */

void write_clk()
{
	uint32_t gpio_outputs;
	MSS_GPIO_config(MSS_GPIO_0,MSS_GPIO_OUTPUT_MODE);

	for (;;){
		gpio_outputs = MSS_GPIO_get_outputs();
		gpio_outputs &= ~( MSS_GPIO_0_MASK);
		MSS_GPIO_set_outputs(gpio_outputs);
	}
}

void write_rst(){

	MSS_GPIO_config(MSS_GPIO_1,MSS_GPIO_OUTPUT_MODE);
	MSS_GPIO_set_outputs(MSS_GPIO_1_MASK);

}
