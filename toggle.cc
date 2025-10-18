#define F_CPU 16000000UL  // 16 MHz clock speed on Arduino Uno

#include "avr/io.h"
#include "avr/interrupt.h"

// Interrupt Service Routine for INT0 (pin 2)
ISR(INT0_vect) {
    // Toggle LED on PB5 (pin 13)
    PORTB ^= (1 << PB5);
}

int main(void) {
    // Set PB5 (pin 13) as output for LED
    DDRB |= (1 << DDB5);
    
    // Set PD2 (pin 2) as input for button
    DDRD &= ~(1 << DDD2);
    
    // Enable internal pull-up on PD2
    PORTD |= (1 << PD2);
    
    // Configure INT0 to trigger on falling edge (button press)
    EICRA |= (1 << ISC01);   // ISC01 = 1
    EICRA &= ~(1 << ISC00);  // ISC00 = 0
    // This sets falling edge (high to low transition)
    
    // Enable INT0 interrupt
    EIMSK |= (1 << INT0);
    
    // Enable global interrupts
    sei();
    
    // Main loop does nothing - interrupt handles everything
    while(1) {
        // Empty loop - all work done in ISR
    }
    
    return 0;
}
