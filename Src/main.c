
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */
#include "MotorController.h"
#include "UserConfig.h"
#include "CommandCode.h"
#include "usbd_cdc_if.h"
#include "Exception.h"
#include "CExceptionConfig.h"
#include "CException.h"
#include "Error.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
//	CEXCEPTION_T ex;
  int Steps[2]={0,0};
  StoreCMD cmd1 = {0,0,0,0};
  Variable xVar = {0,0,0,0};
  Variable yVar = {0,0,0,0};
  Variable x1Var = {0,0,0,0};
  Variable y1Var = {0,0,0,0};
//  Variable zVar = {0,0,0,0};
  Variable fVar = {0,0,0,0};

  VariableMap g00VarTableMapping[] = {
    {'X',&xVar},
    {'Y',&yVar},
//    {'Z',&zVar},
//    {'F',&fVar},
    {NULL,NULL},
  };
  VariableMap g01VarTableMapping[] = {
    {'X',&x1Var},
    {'Y',&y1Var},
//    {'Z',&zVar},
    {'F',&fVar},
    {NULL,NULL},
  };

  GCodeMapping GCode00[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},

    {.name = "G",.code = 1,.varMap = g01VarTableMapping,.doOperation = handleG01},
    {.name = "G",.code = 21,.varMap = NULL,.doOperation = handleG20or21},
    {NULL,NULL,NULL,NULL},
  };

  GCodeMapping GCode00_ONE[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {.name = "G",.code = 1,.varMap = g01VarTableMapping,.doOperation = handleG01},
    {NULL,NULL,NULL,NULL},
  };

  GCodeMapping GCode00_TWO[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {.name = "G",.code = 1,.varMap = g01VarTableMapping,.doOperation = handleG01},
    {NULL,NULL,NULL,NULL},
  };

  GCodeMapping GCode00_THREE[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {.name = "G",.code = 1,.varMap = g01VarTableMapping,.doOperation = handleG01},
    {NULL,NULL,NULL,NULL},
  };

  GCodeMapping GCode00_FOUR[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {.name = "G",.code = 1,.varMap = g01VarTableMapping,.doOperation = handleG01},
    {NULL,NULL,NULL,NULL},
  };
  GCodeMapping GCode00_FIVE[] = {
    {.name = "G",.code = 0,.varMap = g00VarTableMapping,.doOperation = handleG00},
    {.name = "G",.code = 1,.varMap = g01VarTableMapping,.doOperation = handleG01},
    {NULL,NULL,NULL,NULL},
  };


MotorInfo motorX={.name='X', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, \
                  .isReferencing=ISFALSE, .GPIO =MOTOR_STEP_GPIO_PORT, .MotorPin=MOTORX_STEP_PIN};

MotorInfo motorY={.name='Y', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, \
                  .isReferencing=ISFALSE, .GPIO =MOTOR_STEP_GPIO_PORT, .MotorPin=MOTORY_STEP_PIN};

//MotorInfo motorZ={.name='Z', .delta=0, .deltaRef=0, .error=0, .Dostepping=0, \
//                  .isReferencing=ISFALSE, .GPIO =MOTOR_STEP_GPIO_PORT, .MotorPin=MOTORZ_STEP_PIN};

 MotorInfo *MotorInfoTable[] = {
      &motorX,
      &motorY,
     // &motorZ,
       NULL,
     };
  int delta[] = {500,100};
  char *complete = "OK\n";
  char buffer1[100];


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	initialise_monitor_handles();

//
//	  char *SetUp = "G21";
//	  char *line = "G01 Y101 X300 f10";
//
//      cmd1 = decodeGcode(SetUp,GCode00);
//	  cmd1 = decodeGcode(line,GCode00);
//	   for(int i=0;i<3;i++)
//	   {
//	        Steps[i] = g00VarTableMapping[i].var->steps;
//	   }
//	setupMotorInfo(MotorInfoTable,Steps);

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  //DoMotorStepping(MotorInfoTable);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	//HAL_GPIO_TogglePin(MOTOR_STEP_GPIO_PORT,MOTORX_STEP_PIN);
	//HAL_Delay(200);
	//HAL_GPIO_TogglePin(MOTOR_STEP_GPIO_PORT,MOTORY_STEP_PIN);
	//HAL_Delay(200);
	//HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO_PORT,MOTOR_ENABLE_PIN, LOW);
  //configureMotorandStartTimer();
  while (1)
  {
	  DecodeandStepMotor();
//		HAL_GPIO_TogglePin(MOTOR_STEP_GPIO_PORT,MOTORX_STEP_PIN);
//		HAL_Delay(200);
//		HAL_GPIO_TogglePin(MOTOR_STEP_GPIO_PORT,MOTORY_STEP_PIN);
//		HAL_Delay(200);
//		 if(status == DATA_IS_READY)
//		 {
//			 Try{
//			      cmd1 = decodeGcode(buffer,GCode00);
//					memset(buffer,0,sizeof(buffer));
////			 	  cmd1 = decodeGcode(line,GCode00);
//					if(cmd1.code == 1)
//					{
//						E = 1;
//					}
//					else
//					{
//						E = 0;
//					}
//					if(E==0){
//					   for(int i=0;i<3;i++)
//					   {
//							Steps[i] = g00VarTableMapping[i].var->steps;
//					   }
//						   setupMotorInfo(MotorInfoTable,Steps);
//
//						}
//					else{
//					 	   for(int i=0;i<3;i++)
//					 	   {
//					 	        Steps[i] = g01VarTableMapping[i].var->steps;
//					 	   }
//					 	setupMotorInfo(MotorInfoTable,Steps);
//					}
//			 	configureMotorandStartTimer();
////			 	HAL_TIM_Base_Start_IT(&htim2);
//			 	while(MOTORSTATUS != MOTOR_OK)
//			 	{
//			 	}
//			 if(MOTORSTATUS == MOTOR_OK)
//			 {
//				 CDC_Transmit_FS(complete,strlen(complete));
//				 MOTORSTATUS = MOTOR_DO_NEXT;
//				 status = WAIT_FOR_NXT_CMD;
////				 buffer[0] = 0;
//				 //memset(input,0,sizeof(input));
//			 }
//			}
//			 Catch(ex)
//			 {
//				 dumpException(ex);
//				 if(ex!=NULL){
//				 snprintf(buffer1, 100, "%s %c (err=%d)\n",ex->msg,ex->data,ex->errorCode);
//				 CDC_Transmit_FS(buffer1, strlen(buffer1));
//				 }
//				 freeException(ex);
//				 status = WAIT_FOR_NXT_CMD;
//				 volatile int i;
//				 //CDC_Transmit_FS(ex->msg, strlen(ex->msg));
//			 }
//		 }

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */


  /* USER CODE END 3 */

  }
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 2400;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 38;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void settimer2Periodvalue(int value){
	htim2.Instance->ARR = value;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
