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
#define Microsemi_logo \
"\n\r \
** ** ******* ****** ***** **** ***** ****** ** ** ******* \n\r \
* * * * * * * * * * * * * * * * * \n\r \
* * * * * * ***** * * **** ****** * * * * * \n\r \
* * * * * * * * * * * * * * * \n\r \
* * ******* ****** * * **** ***** ****** * * ******* "
/* Main function */


/*==============================================================================
 * main() function.
 */
int main()
{
	const uint8_t greeting[] = "\n\rWelcome to SmartFusion "
	"- customizable system-on-chip (cSoC)";

	/* Initialize and configure UART0. */
	 MSS_UART_init
	 (
	 &g_mss_uart0,
	 MSS_UART_57600_BAUD,
	 MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT
	 );
	 /* Send the Microsemi Logo over the UART_0 */

	 MSS_UART_polled_tx_string( &g_mss_uart0, (const uint8_t *)Microsemi_logo);

	 /* Send greeting message over the UART_0 */

	 MSS_UART_polled_tx( &g_mss_uart0, greeting, sizeof(greeting) );

	 while(1){

	 }

	 return(0);
}

