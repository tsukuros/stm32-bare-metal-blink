#include "stm32f446xx.h"

// Called by Reset_Handler before main. HAL uses this for clock setup.
// We configure registers directly in main, so this is intentionally empty.
void SystemInit(void) {}

// Required by newlib's __libc_init_array (C runtime init hook).
void _init(void) {}

int main(void) {
  // RM0390 §6.3.9: AHB1ENR bit 0 = GPIOAEN. GPIO peripheral registers are
  // clock-gated by default — writing them before enabling the clock has no
  // effect. Must be set before any GPIOA access.
  RCC->AHB1ENR |= (1 << 0);

  // RM0390 §8.4.1: MODER is 2 bits per pin. PA5 occupies bits [11:10].
  // Clear both bits first (read-modify-write) so we start from a known state
  // before setting the new mode. Skipping the clear risks leaving stale bits.
  GPIOA->MODER &= ~(0x3 << 10);

  // MODER bits 00=input, 01=output, 10=alternate function, 11=analog.
  // We want 01 (general-purpose output) to drive LD2 on PA5.
  GPIOA->MODER |=  (0x1 << 10);

  while (1) {
    // ODR bit 5 controls PA5 output level. XOR with 1 flips it each iteration
    // without needing to track current state — the register holds the state.
    GPIOA->ODR ^= (1 << 5);

    // No SysTick configured yet, so delay is a busy-wait loop. The volatile
    // qualifier prevents the compiler from optimizing the loop away entirely.
    // 500 000 iterations ≈ 1 s at 16 MHz HSI (default after reset).
    for (volatile uint32_t i = 0; i < 500000; i++);
  }
}