#include <WProgram.h>
#include "clockdisplay.h"

static const int led_base = 0, led_pins = 7, col_base = 8, col_pins = 4;
// LEDs: t tr br b   bl tl m _
static const unsigned char digits[11] = {
	0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6, 0x00};

static void cdisp_digit(unsigned char d) {
	int i;
	d = digits[d];
	for (i = 1; i <= led_pins; i++) {
		d >>= 1;
		digitalWrite(led_base + led_pins - i, d & 1 ? HIGH : LOW);
	}
}

void cdisp_number(unsigned short num, int msec) {
	unsigned long now, start = millis();
	unsigned char cols[col_pins];
	int c;

	/* determine each column's digit */
	for (c = 0; c < col_pins; c++) {
		digitalWrite(col_base + c, HIGH);
		cols[col_pins - c - 1] = (num || !c) ? num % 10 : 10;
		num /= 10;
	}

	do {
		/* display each digit rapidly in succession */
		for (c = 0; c < col_pins; c++) {
			digitalWrite(col_base + c, LOW);
			cdisp_digit(cols[c]);
			delay(5);
			digitalWrite(col_base + c, HIGH);
		}
		now = millis();
	} while (now >= start && now < start + msec);
}

void cdisp_setup(void) {
	int i;
	for (i = led_base; i < led_base+led_pins; i++)
		pinMode(i, OUTPUT);
	for (i = col_base; i < col_base+col_pins; i++) {
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}
}
