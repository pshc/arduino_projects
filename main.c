#include <WProgram.h>
#include "clockdisplay.h"

static volatile int ctr = 0;

/* TODO: for some reason this gets called continuously except when sending
         HIGH from the transmitter */
static void rf_handler(void) {
	if (++ctr > 9999) ctr = 0;
}

int main(void) {
	init();
	cdisp_setup();
	attachInterrupt(0, &rf_handler, RISING); /* pin 2 */

	while (1) {
		cdisp_number(ctr, 50);
	}
	return 0;
}

