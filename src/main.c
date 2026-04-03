#include "stm32f446xx.h"

// Called by Reset_Handler before main. HAL uses this for clock setup.
// We configure registers directly in main, so this is intentionally empty.
void SystemInit(void) {}

// Required by newlib's __libc_init_array (C runtime init hook).
void _init(void) {}

int main(void) {
  RCC->AHB1ENR |= (1 << 0);       // enable GPIOA clock
  GPIOA->MODER &= ~(0x3 << 10);   // clear PA5 mode bits
  GPIOA->MODER |=  (0x1 << 10);   // PA5 = general-purpose output

  while (1) {
    GPIOA->ODR ^= (1 << 5);                          // toggle PA5 (LD2)
    for (volatile uint32_t i = 0; i < 500000; i++);  // ~1s busy-wait
  }
}