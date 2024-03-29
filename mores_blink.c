#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
int DOT_TIME = 250;
int DASH_TIME = 750;
int WORD_SEPERATE_TIME = 1000;
char* HELLO_MSG = "HELLO";
char* SOS_MSG = "SOS";


//Hardware millisecond timer
void delay(unsigned short ms){

	SIM->SCGC6 |= (1 << 24);
	SIM->SOPT2 |= (0x2 << 24);
	TPM0->CONF |= (0x1 << 17);
	TPM0->SC = (1 << 7) | (0x7);

	TPM0->MOD = ms*62 + ms/2 - 1;

	TPM0->SC |= 0x01 << 3;

	while (!(TPM0->SC & 0x80)) {}
}

int displayDot() {
	GPIOD->PTOR |= (1 << 5);
	delay(DOT_TIME);
	GPIOD->PTOR |= (1 << 5);
	return 0;
}

int displayDash() {
	GPIOD->PTOR |= (1 << 5);
	delay(DASH_TIME);
	GPIOD->PTOR |= (1 << 5);
	return 0;
}

void displayMorse(char* message, int length) {
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; // PORT D mask connected to Green LED
	PORTD->PCR[5] = PORT_PCR_MUX(1);

	for(int i = 0; i < length; ++i) {
		if(message[i] == 'A') {
			 displayDot();
			 delay(DOT_TIME);
			 displayDash();
		}
		else if(message[i] == 'B') {
			displayDash();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'C') {
			displayDash();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'D') {
			displayDash();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
		}
		else if(message[i] == 'E') {
			displayDot();
		}
		else if(message[i] == 'F') {
			displayDot();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'G') {
			displayDash();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'H') {
			displayDot();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'I') {
			displayDot();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'J') {
			displayDot();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDash();
		}
		else if(message[i] == 'K') {
			displayDash();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDash();
		}
		else if(message[i] == 'L') {
			displayDot();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'M') {
			displayDash();
			delay(DOT_TIME);
			displayDash();
		}

		else if(message[i] == 'N') {
			displayDash();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'O') {
			displayDash();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDash();
		}
		else if(message[i] == 'P') {
			displayDot();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'R') {
			displayDot();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'S') {
			displayDot();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDot();
		}
		else if(message[i] == 'T') {
			displayDash();
		}
		else if(message[i] == 'U') {
			displayDot();
		    delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDash();
		}
		else if(message[i] == 'V') {
			displayDot();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDash();
		}
		else if(message[i] == 'W') {
			displayDot();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDash();
		}
		else if(message[i] == 'X') {
			displayDash();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDash();
		}
		else if(message[i] == 'Y') {
			displayDash();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDash();
		}
		else if(message[i] == 'Z') {
			displayDash();
			delay(DOT_TIME);
			displayDash();
			delay(DOT_TIME);
			displayDot();
			delay(DOT_TIME);
			displayDot();
		}

		(void) delay(DASH_TIME);
	}

}

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("== Morse code == \n");

    SIM->SCGC5 |= 1<<12;

    PORTD->PCR[5] &= ~0x700;
    PORTD->PCR[5] |= 0x700 & (1 << 8);
    GPIOD->PDDR |= (1 << 5);
    
    PRINTF("converting HELLO to morse code blinking");
    displayMorse(HELLO_MSG, 5);

    delay(2000);

    PRINTF("converting SOS to morse code blinking");
    displayMorse(SOS_MSG, 3);

    while(1) {
    }
    return 0 ;
}
