#include "stm32f446xx.h"

int main() {
  RCC->AHB1ENR |= (1 << 0); // enable GPIOA clock
  GPIOA->MODER &= ~(0x3 << 10);
  GPIOA->MODER |= (0x1 << 10);
  while (1) {
    GPIOA->ODR ^= (1 << 5);
    for (volatile uint32_t i = 0; i < 500000; i++)
      ;
  }
}