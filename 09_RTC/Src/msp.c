/*
 * msp.c
 *
 *  Created on: Nov 26, 2025
 *      Author: Admin
 */

#include "stm32f7xx_hal.h"

void HAL_MspInit(void)
{
    // Initialize the Global MSP.
    // This function is called at the beginning of HAL_Init().
    
    //1. Set up the priority grouping of the ARM Cortex-Mx Processor
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    // 2. Enable the required system exceptions of the ARM Cortex-Mx Processor
    SCB->SHCSR |= (0x07 << 16);  // Enable MemManage, BusFault and UsageFault exceptions
    
    // 3. Configure the priority of the system exceptions
    HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0); // MemManage exception
    HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);          // BusFault exception
    HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);        // UsageFault exception

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    // here we are going to do the low level initialization of the UART2 peripheral
    GPIO_InitTypeDef gpio_uart;
    // 1. Enable the peripheral clock for UART2 and GPIOA
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 2. Do the pin muxing configurations
    gpio_uart.Pin = GPIO_PIN_2; // PA2->TX
    gpio_uart.Mode = GPIO_MODE_AF_PP;
    gpio_uart.Pull = GPIO_PULLUP;
    gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
    gpio_uart.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &gpio_uart);

    gpio_uart.Pin = GPIO_PIN_3; // PA3->RX
    HAL_GPIO_Init(GPIOA, &gpio_uart);

    // 3. Enable the IRQ and set up the priority (NVIC settings)
    HAL_NVIC_EnableIRQ(USART2_IRQn);
}

void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_CAN1_CLK_ENABLE();

	/**CAN1 GPIO Configuration
	PA11     ------> CAN1_RX
	PA12     ------> CAN1_TX
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(CAN1_TX_IRQn,15,0);
  HAL_NVIC_SetPriority(CAN1_RX0_IRQn,15,0);
  HAL_NVIC_SetPriority(CAN1_RX1_IRQn,15,0);
  HAL_NVIC_SetPriority(CAN1_SCE_IRQn,15,0);

  HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
  HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
  HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
}