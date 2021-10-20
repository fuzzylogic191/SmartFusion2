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

/* Function Decelerations */
int  char_2_int(char);
void disp_code(int);

void clr_reset();
void set_reset();
void pulse_reset(uint8_t);
void set_clk(uint8_t);
void clr_clk();



/*==============================================================================
 * main() function.
 */
#define RX_BUFF_SIZE 64
int main()
{
	uint8_t rx_buff[64];
	uint32_t rx_idx  = 0;
	uint32_t rx_size;
	int opcode;

	//Initialize Registers
	MSS_GPIO_init();
	MSS_UART_init(&g_mss_uart0,MSS_UART_9600_BAUD,MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);

	//=========================================================================
	while (1){
		rx_size = MSS_UART_get_rx(&g_mss_uart0, rx_buff, sizeof(rx_buff));
		if( rx_size > 0 ){
		opcode = char_2_int(rx_buff[0]);
		disp_code(opcode);
		}

	}//loop

	 return(0);
}

int char_2_int(char code){
	int opc;
	opc = code;
	return (opc);
}

void disp_code(int opc){
	switch (opc){
	case 48:
		MSS_UART_polled_tx_string(&g_mss_uart0, "clr_reset ");
		break;
	case 49:
		MSS_UART_polled_tx_string(&g_mss_uart0, "set_reset ");
		break;
	case 50:
		MSS_UART_polled_tx_string(&g_mss_uart0, "pulse_reset ");
		break;
	case 51:
		MSS_UART_polled_tx_string(&g_mss_uart0, "set_clk ");
		break;
	case 52:
		MSS_UART_polled_tx_string(&g_mss_uart0, "clr_clk ");
		break;
	default:
		MSS_UART_polled_tx_string(&g_mss_uart0, "Please enter a valid command ");
		break;
	}//int switch
}

/* If called this function clears the value on the reset pin;
 * and sets it low/off
 */
void clr_reset(){


}

/* If called this function turns the reset pin on/pulls it high
 * for an indeterminate period of time
 */
void set_reset(){

}

/* Creates a pulse reset at a constant period
 * Takes period as an input
 */
void pulse_reset(uint8_t period){

}

/*Sets the clock to a determined frequency
 *
 */
void set_clk(uint8_t freq){


}

/* This function clears the clock
 * '/' sets it low
 */
void clr_clk(){


}
