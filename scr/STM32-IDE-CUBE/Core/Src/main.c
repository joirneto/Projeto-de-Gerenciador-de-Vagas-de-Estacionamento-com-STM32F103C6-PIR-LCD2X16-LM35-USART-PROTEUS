/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//INCLUSÃO DA BIBLIOTECA PARA UTILIZAÇÃO DO LCD 2X16
#include "lcd.h"
#include "stdio.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

//CRIANDO AS VARIÁVEIS PARA ACD E USART
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// CRIANDO AS VARIÁVEIS DE TRABALHO
static int adc_buffer;
static char s_vagas[5];
static char temp[5];

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  //INICIALIZANDO A VARIÁVEL COM O NÚMERO DE VAGAS
  int vagas = 5;

  //INICIALIZANDO O ACD
  HAL_ADC_Start(&hadc1);

  //CONFIGURADO AS GPIOs  -- GPIOA RENOMEADAS COM AS IDENTIFICAÇÕES DO LCD
  Lcd_PortType ports [] = {
		D4_GPIO_Port,
		D5_GPIO_Port,
		D6_GPIO_Port,
		D7_GPIO_Port
  };

  //CONFIGURADO OS PINOS DO LCD
  Lcd_PinType pins [] = {
		D4_Pin,
		D5_Pin,
		D6_Pin,
		D7_Pin
  };

  //CONFIGURADO OS PINOS DO LCD COM AS GPIOs
  Lcd_HandleTypeDef lcd = Lcd_create(ports, pins, RS_GPIO_Port, RS_Pin, EN_GPIO_Port, EN_Pin, LCD_4_BIT_MODE);

  //PARA IMPRIMIR NO LCD - PASSAR O ENDEREÇO DO OBJETO E A POSIÇÃO DO CURSOR
  Lcd_cursor(&lcd, 0, 0);
  Lcd_string(&lcd,"ESTACIONAMENTO");
  Lcd_cursor(&lcd, 1, 0);
  Lcd_string(&lcd,"DEDEL");
  HAL_Delay(50);
  Lcd_clear(&lcd);
  HAL_Delay(50);

  Lcd_cursor(&lcd, 0, 0);
  Lcd_string(&lcd,"SEJA");
  Lcd_cursor(&lcd, 1, 0);
  Lcd_string(&lcd,"BEM-VINDO");
  HAL_Delay(50);
  Lcd_clear(&lcd);
  HAL_Delay(50);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(((float)HAL_ADC_GetValue(&hadc1)/8.215)<=30){
		  if(vagas!=0){
			  //IMPRIMINDO O NÚMEROS DE VAGAS NO LCD
			  Lcd_cursor(&lcd, 0, 0);
			  Lcd_string(&lcd,"VAGAS");
			  Lcd_cursor(&lcd, 1, 0);
			  Lcd_string(&lcd,"DIPONIVEIS= ");
			  // Convertendo de inteiro para String
			  itoa(vagas, s_vagas, 10);
			  Lcd_cursor(&lcd, 1, 12);
			  Lcd_string(&lcd, s_vagas);
			  HAL_Delay(100);
			  Lcd_clear(&lcd);

			  //VERIFICANDO SE OCORREU ENTRADA DE VEÍCULOS
			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)){
				 if(vagas!=0){
					 vagas--;
					 while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)){
						 Lcd_cursor(&lcd, 0, 0);
						 Lcd_string(&lcd,"AGUARDE");
					 }
					 Lcd_clear(&lcd);
					 Lcd_cursor(&lcd, 0, 0);
					 Lcd_string(&lcd,"SIGA EM FRETE");
					 HAL_Delay(50);
				 }
				 else{
					 Lcd_cursor(&lcd, 0, 0);
					 Lcd_string(&lcd,"LOTADO");
					 HAL_Delay(100);
				 }

				 Lcd_clear(&lcd);
			  }

			  //VERIFICANDO SE OCORREU SAÍDA DE VEÍCULOS
			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)){
				  if(vagas<5){
					vagas++;
					while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)){
						 Lcd_cursor(&lcd, 0, 0);
						 Lcd_string(&lcd,"AGUARDE");
					 }
					Lcd_clear(&lcd);
					Lcd_cursor(&lcd, 0, 0);
					Lcd_string(&lcd,"OBRIGADO");
					Lcd_cursor(&lcd, 1, 0);
					Lcd_string(&lcd,"VOLTE SEMPRE");
					HAL_Delay(50);
				  }
				  else{
					  Lcd_cursor(&lcd, 0, 0);
					  Lcd_string(&lcd,"DISPONIVEL");
					  HAL_Delay(100);
				  }
				  Lcd_clear(&lcd);
			  }

			  //Utilizando função HAL para coletar o valor de ACD
			  //O sensor LM35 envia valores entre 0 e 1023
			  //Portanto realizamos a conversão para o valor em graus dividindo por 8,125
			  adc_buffer = (float)HAL_ADC_GetValue(&hadc1)/8.215;

			  //ENVIADO DADOS ATRAVÉS DA USART
			  uint8_t CRLFbuff[] = " C\r\n";
			  uint8_t Tempbuff[] = "T: ";
			  HAL_UART_Transmit(&huart1, Tempbuff, 3, 0xFF);
			  HAL_UART_Transmit(&huart1, (uint8_t*)temp, sprintf(temp, "%d",adc_buffer ), 100);
			  HAL_UART_Transmit(&huart1, CRLFbuff, 3, 0xFF);

			  //IMPRIMINDO A TEMPERATURA NO LCD
			  Lcd_cursor(&lcd, 0, 0);
			  Lcd_string(&lcd,"TEMPERATURA");
			  Lcd_cursor(&lcd, 1, 0);
			  Lcd_string(&lcd,temp);
			  Lcd_cursor(&lcd, 1, 2);
			  Lcd_string(&lcd,"C");
			  HAL_Delay(50);
			  Lcd_clear(&lcd);
		  }
		  else{

			  //IMPRIMINDO A ESTACIONAMENTO LOTADO
			  Lcd_cursor(&lcd, 0, 0);
			  Lcd_string(&lcd,"ESTACIONAMENTO");
			  Lcd_cursor(&lcd, 1, 0);
			  Lcd_string(&lcd,"LOTADO");
			  HAL_Delay(50);
			  Lcd_clear(&lcd);

			  //VERIFICANDO SE OCORREU SAÍDA DE VEÍCULOS
			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)){
				  if(vagas<5){
					vagas++;
					while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)){
						 Lcd_cursor(&lcd, 0, 0);
						 Lcd_string(&lcd,"AGUARDE");
					 }
					Lcd_clear(&lcd);
					Lcd_cursor(&lcd, 0, 0);
					Lcd_string(&lcd,"OBRIGADO");
					Lcd_cursor(&lcd, 1, 0);
					Lcd_string(&lcd,"VOLTE SEMPRE");
					HAL_Delay(50);
				  }
				  else{
					  Lcd_cursor(&lcd, 0, 0);
					  Lcd_string(&lcd,"DISPONIVEL");
					  HAL_Delay(100);
				  }
				  Lcd_clear(&lcd);
			  }

		  }
	  }
	  else{
		  //IMPRIMINDO A INCENDIO
		  Lcd_cursor(&lcd, 0, 0);
		  Lcd_string(&lcd,"INCENDIO");
		  Lcd_cursor(&lcd, 1, 0);
		  Lcd_string(&lcd,"EVACUAR NOW!");
		  HAL_Delay(50);
		  Lcd_clear(&lcd);
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D4_Pin|D5_Pin|D6_Pin|D7_Pin
                          |RS_Pin|EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin
                           RS_Pin EN_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin
                          |RS_Pin|EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
