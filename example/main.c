#include <msp430.h>
#include "../ws2812.h"

void gradualFill(u_int n, u_char r, u_char g, u_char b);

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
	#ifdef CLOCK_8MHZ
    if (CALBC1_8MHZ==0xFF)    // If calibration constant erased
	#else
    if (CALBC1_16MHZ==0xFF)    // If calibration constant erased
	#endif
    {
        while(1);              // do not load, trap CPU!!
    }

    // configure clock to 8/16 MHz
	#ifdef CLOCK_8MHZ
    BCSCTL1 = CALBC1_8MHZ;    // DCO = 8 MHz
    DCOCTL = CALDCO_8MHZ;
	#else
    BCSCTL1 = CALBC1_16MHZ;    // DCO = 16 MHz
    DCOCTL = CALDCO_16MHZ;
	#endif

    // initialize LED strip
    initStrip();  // ***** HAVE YOU SET YOUR NUM_LEDS DEFINE IN WS2812.H? ******

    // set strip color red
    fillStrip(0x00, 0x00, 0x00);

    // show the strip
    showStrip();

    // gradually fill for ever and ever
    while (1) {
        gradualFill(NUM_LEDS, 0x00, 0xFF, 0x00);  // green
        gradualFill(NUM_LEDS, 0x00, 0x00, 0xFF);  // blue
        //gradualFill(NUM_LEDS, 0xFF, 0x00, 0xFF);  // magenta
        //gradualFill(NUM_LEDS, 0xFF, 0xFF, 0x00);  // yellow
        //gradualFill(NUM_LEDS, 0x00, 0xFF, 0xFF);  // cyan
        gradualFill(NUM_LEDS, 0xFF, 0x00, 0x00);  // red
    }
}

void gradualFill(u_int n, u_char r, u_char g, u_char b){
    int i;
    for (i = 0; i < n; i++){        // n is number of LEDs
        setLEDColor(i, r, g, b);
        showStrip();
        __delay_cycles(1500000);       // lazy delay
    }
}
