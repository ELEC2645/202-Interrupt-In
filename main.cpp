/* 
 
2645_InterruptIn
 
Sample code from ELEC2645 
 
Demonstrates how to use InterruptIn to generate an event-triggered interrupt
 
(c) Craig A. Evans, University of Leeds, Jan 2016
 
*/ 
 
#include "mbed.h"
 
// Create objects for A button and red LED 1
InterruptIn A_button(PTC7);
DigitalOut red_led(PTA2);
 
// flag - must be volatile as changes within ISR
// g_ prefix makes it easier to distinguish it as global
volatile int g_A_button_flag = 0;
 
// function prototypes
void A_button_isr();
 
int main()
{
    // Use the internal pull up resistor.
    A_button.mode(PullUp);
    // A_button is configured as pull up so the pin will be at 3.3 V by default
    // and fall to 0 V when pressed. We therefore need to look for a falling edge
    // on the pin to fire the interrupt
    A_button.fall(&A_button_isr);
    
    
    // the on-board RGB LED is a common anode - writing a 1 to the pin will turn the LED OFF
    red_led = 1;
 
    while (1) {
 
        // check if flag i.e. interrupt has occured
        if (g_A_button_flag) {
            g_A_button_flag = 0;  // if it has, clear the flag
 
            // send message over serial port - can observe in CoolTerm etc.
            printf("Execute task \n");
            // DO TASK HERE
        }
 
        // put the MCU to sleep until an interrupt wakes it up
        sleep();
 
    }
}
 
// A_button event-triggered interrupt
void A_button_isr()
{
    g_A_button_flag = 1;   // set flag in ISR
}
 