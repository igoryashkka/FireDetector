/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim3;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
	        static uint8_t ledState = 0;
	        if (ledState == 0)
	        {
	            LED_On();
	            ledState = 1;
	        }
	        else
	        {
	            LED_Off();
	            ledState = 0;
	        }
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void Process_UART_Command(char *command) {
    if (strcmp(command, "get_humidity") == 0) {
        snprintf(uart_tx_buffer, UART_BUFFER_SIZE, "DEV: get_humidity %.1f\n", humidity);
        HAL_UART_Transmit(&huart1, (uint8_t*)uart_tx_buffer, strlen(uart_tx_buffer), HAL_MAX_DELAY);
    } else if (strcmp(command, "get_temperature") == 0) {
        snprintf(uart_tx_buffer, UART_BUFFER_SIZE, "DEV: get_temperature %.1f\n", temperature);
        HAL_UART_Transmit(&huart1, (uint8_t*)uart_tx_buffer, strlen(uart_tx_buffer), HAL_MAX_DELAY);
    } else if (strcmp(command, "get_ppm") == 0) {
        snprintf(uart_tx_buffer, UART_BUFFER_SIZE, "DEV: get_ppm %d\n", value_ppm);
        HAL_UART_Transmit(&huart1, (uint8_t*)uart_tx_buffer, strlen(uart_tx_buffer), HAL_MAX_DELAY);
    } else if (strncmp(command, "set_buzzer ", 11) == 0) {
        if (strcmp(&command[11], "on") == 0) {
            HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
            snprintf(uart_tx_buffer, UART_BUFFER_SIZE, "DEV response: set_buzzer on\n");
        } else if (strcmp(&command[11], "off") == 0) {
            HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
            snprintf(uart_tx_buffer, UART_BUFFER_SIZE, "DEV response: set_buzzer off\n");
        }
        HAL_UART_Transmit(&huart1, (uint8_t*)uart_tx_buffer, strlen(uart_tx_buffer), HAL_MAX_DELAY);
    } else if (strncmp(command, "set_led ", 8) == 0) {
        if (strcmp(&command[8], "on") == 0) {
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
            snprintf(uart_tx_buffer, UART_BUFFER_SIZE, "DEV response: set_led on\n");
        } else if (strcmp(&command[8], "off") == 0) {
            HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
            snprintf(uart_tx_buffer, UART_BUFFER_SIZE, "DEV response: set_led off\n");
        }
        HAL_UART_Transmit(&huart1, (uint8_t*)uart_tx_buffer, strlen(uart_tx_buffer), HAL_MAX_DELAY);
    } else {
        snprintf(uart_tx_buffer, UART_BUFFER_SIZE, "DEV: unknown_command\n");
        HAL_UART_Transmit(&huart1, (uint8_t*)uart_tx_buffer, strlen(uart_tx_buffer), HAL_MAX_DELAY);
    }
}


/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
