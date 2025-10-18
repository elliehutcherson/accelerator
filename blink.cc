#define F_CPU 16000000UL  // 16 MHz clock speed on Arduino Uno

#include "avr/io.h"

#include "util/delay.h"

int main(void) {
    // Set PB5 (pin 13) as output
    DDRB |= (1 << DDB5);
    
    while(1) {
        // Turn LED on (set PB5 high)
        PORTB |= (1 << PB5);
        _delay_ms(500);  // Wait 500 milliseconds

        // Turn LED off (set PB5 low)
        PORTB &= ~(1 << PB5);
        _delay_ms(5000);  // Wait 5 seconds
    }
    
    return 0;
}
