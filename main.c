/**
 * @file main.c
 * @brief Bare-metal C LED blink application using Timer0 CTC Interrupts
 * @target ATmega328P (16MHz clock)
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

// Onboard LED is connected to Port B, Pin 5 (Digital Pin 13 on Arduino Uno)
#define LED_PIN PB5

// Global tick counter updated inside Timer0 ISR
static volatile uint32_t g_ticks_ms = 0;

/**
 * @brief Timer0 Compare Match A Interrupt Service Routine
 * @details Fires every 1ms to increment system tick counter
 */
ISR(TIMER0_COMPA_vect) {
    g_ticks_ms++;
}

/**
 * @brief Atomic read of millisecond system clock
 */
static uint32_t get_millis(void) {
    uint32_t ms;
    cli(); // Disable global interrupts briefly
    ms = g_ticks_ms;
    sei(); // Re-enable global interrupts
    return ms;
}

/**
 * @brief Hardware setup using direct register writes
 */
static void Hardware_Init(void) {
    // 1. Set PB5 as OUTPUT in Data Direction Register B
    DDRB |= (1U << LED_PIN);

    // Turn LED off initially
    PORTB &= ~(1U << LED_PIN);

    // 2. Configure Timer0 for 1ms system interrupts
    // Set CTC (Clear Timer on Compare Match) mode: WGM01 = 1, WGM00 = 0
    TCCR0A = (1U << WGM01);

    // Set clock prescaler to 64: CS01 = 1, CS00 = 1
    TCCR0B = (1U << CS01) | (1U << CS00);

    // Compare value = (16MHz / (64 * 1000Hz)) - 1 = 249
    OCR0A = 249;

    // Enable Timer0 Output Compare Match A Interrupt
    TIMSK0 |= (1U << OCIE0A);

    // Enable Global Interrupts (Set I-bit in Status Register SREG)
    sei();
}

int main(void) {
    Hardware_Init();

    uint32_t last_toggle_time = 0;

    while (1) {
        // Non-blocking delay check (toggles every 500ms)
        if (get_millis() - last_toggle_time >= 500) {
            last_toggle_time = get_millis();

            // Toggle LED using XOR on PORTB register
            PORTB ^= (1U << LED_PIN);
        }
    }

    return 0;
}