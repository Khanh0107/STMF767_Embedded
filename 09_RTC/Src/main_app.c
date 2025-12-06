/*
 * main.c
 *
 *  Created on: Nov 26, 2025
 *      Author: Admin
 */

#include "stm32f7xx_hal.h"
#include <string.h>
#include "main.h"
#include <stdio.h>

void SystemClock_Config(void);
void UART2_Init(void);
void Error_Handler(void);
void GPIO_Init(void);
void CAN1_Init(void);
void CAN1_Tx(void);
void CAN1_Rx(void);
void CAN_Filter_Config(void);

UART_HandleTypeDef huart2;
CAN_HandleTypeDef hcan1;

char *user_data = "Message prepare.\n";
char *user_data1 = "Message transmitted via CAN1: HELLO\r\n";
int main(void)
{
    // Initialize the HAL Library
    HAL_Init();

    GPIO_Init();
    UART2_Init();
    
    
    CAN1_Init();
    // uint32_t apb1 = HAL_RCC_GetPCLK1Freq();
    // char msg[100];
    // sprintf(msg, "APB1: %lu Hz, Prescaler: 2, BS1:13, BS2:2 => Bitrate: %lu bps\r\n",
    //         apb1, apb1 / (2 * (1 + 13 + 2)));
    // HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

    CAN_Filter_Config();

    if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_BUSOFF) != HAL_OK)
    {
        Error_Handler();
    }

    CAN1_Tx();

    // CAN1_Rx();

    // Main loop
    while (1)
    {
        // Your application code
    }
    return 0;
}


void GPIO_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef ledgpio;
  ledgpio.Pin = GPIO_PIN_5;
  ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
  ledgpio.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA,&ledgpio);
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}


void CAN1_Init(void)
{
    hcan1.Instance = CAN1;
    hcan1.Init.Mode = CAN_MODE_LOOPBACK;
    hcan1.Init.AutoBusOff = ENABLE;
    hcan1.Init.AutoRetransmission = ENABLE;
    hcan1.Init.AutoWakeUp = DISABLE;
    hcan1.Init.ReceiveFifoLocked = DISABLE;
    hcan1.Init.TimeTriggeredMode = DISABLE;
    hcan1.Init.TransmitFifoPriority = DISABLE;

    hcan1.Init.Prescaler = 2;           // điều chỉnh nếu clock APB1 khác
    hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
    hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;

    if (HAL_CAN_Init(&hcan1) != HAL_OK)
    {
        Error_Handler();
    }

    /* Bắt đầu CAN peripheral */
    if (HAL_CAN_Start(&hcan1) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
    char msg[50];
  sprintf(msg,"Message Transmitted:M0\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);
}

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
{
    char msg[50];
  sprintf(msg,"Message Transmitted:M1\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);
}

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
{
    char msg[50];
  sprintf(msg,"Message Transmitted:M2\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef RxHeader;
  uint8_t rcvd_msg[5];

  char msg[50];

  if(HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&RxHeader,rcvd_msg) != HAL_OK)
  {
    Error_Handler();
  }

  sprintf(msg,"Message Received : %s\r\n",rcvd_msg);

  HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
    char msg[50];
    sprintf(msg,"CAN Error Detected\r\n");
    HAL_UART_Transmit(&huart2,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY);
}

void CAN1_Tx(void)
{

    CAN_TxHeaderTypeDef TxHeader;

    uint32_t TxMailbox;

    uint8_t TxData[5] = {'H', 'E', 'L', 'L', 'O'};

    TxHeader.DLC = 5;
    TxHeader.StdId = 0x65D;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;

    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
    {
        // Transmission request Error
        Error_Handler();
    }

    // if (HAL_UART_Transmit(&huart2, (uint8_t *)user_data, strlen(user_data), HAL_MAX_DELAY) != HAL_OK)
    // {
    //     // Transmission Error
    //     Error_Handler();
    // }

    while (HAL_CAN_IsTxMessagePending(&hcan1, TxMailbox));

    // if (HAL_UART_Transmit(&huart2, (uint8_t *)user_data1, strlen(user_data1), HAL_MAX_DELAY) != HAL_OK)
    // {
    //     // Transmission Error
    //     Error_Handler();
    // }
}

void CAN1_Rx(void)
{
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t rcvd_msg[5];

    //   Wait until a message is received
    while (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) == 0);

    if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, rcvd_msg) != HAL_OK)
    {
        // Reception Error
        Error_Handler();
    }
}

void CAN_Filter_Config(void)
{
    CAN_FilterTypeDef can1_filter_init;

    can1_filter_init.FilterActivation = ENABLE;
    can1_filter_init.FilterBank = 0;
    can1_filter_init.FilterFIFOAssignment = CAN_RX_FIFO0;
    can1_filter_init.FilterIdHigh = 0x0000;
    can1_filter_init.FilterIdLow = 0x0000;
    can1_filter_init.FilterMaskIdHigh = 0x0000;
    can1_filter_init.FilterMaskIdLow = 0x0000;
    can1_filter_init.FilterMode = CAN_FILTERMODE_IDMASK;
    can1_filter_init.FilterScale = CAN_FILTERSCALE_32BIT;

    if (HAL_CAN_ConfigFilter(&hcan1, &can1_filter_init) != HAL_OK)
    {
        Error_Handler();
    }
}
    
void UART2_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        // Initialization Error
        Error_Handler();
    }
}

void Error_Handler(void)
{
    // User can add his own implementation to report the HAL error return state
    while(1)
    {
    }
}
