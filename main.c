#include <WProgram.h>
#include "clockdisplay.h"

int main(void) {
	init();
	cdisp_setup();
	unsigned short ctr = 0;

	while (1) {
		cdisp_number(ctr++, 100);
		if (ctr > 9999) ctr = 0;
	}
	return 0;
}

