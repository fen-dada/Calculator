/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//PA0-3:line of the keyboard 
//PA4,6,8,15:lie of the keyboard 
//PA5 SCK
//PA7 SDK
//PB10,11,12:RES,DC,CS
#include "calc.h"
#include "value.h"
#include "keyboard.h"
#include "oled.h"
#include "gui.h"
#include "u8g2.h"
#include "u8x8.h"
#include<stdbool.h>
//UART_HandleTypeDef huart1;

int x=0,x_trg=64,y=10,y_trg=10;
int f_len,f_len_trg,f_y=10,f_y_trg,f_x=0,f_x_trg,f_h,f_h_trg;
int ui_func_select=0;
int ui_menu_select=0;
int menu_x=0,menu_y=20,menu_x_trg=0,menu_y_trg=20;
int equa_x=0,equa_x_trg=64,equa_y=10,equa_y_trg=10;
int ui_equa_select=0;
int equa_2_select=0,equa_3_select=0,equa_4_select=0;
int ef_x=0,ef_y=10,ef_y_trg,ef_x_trg,ef_len,ef_len_trg,ef_h,ef_h_trg;
int idx=0;
int key_state=0;
int def_select=0;
List list[] = {
	{"sinx",4},
	{"cosx",4},
	{"tanx",4},
	{"arcsinx",7},
	{"arccosx",7},
	{"arctanx",7},
	{"log",3},
	{"ln",2},
	{"e^x",3},
	{"a^x",3},
};
Key key[2];
Key_msg key_msg; 
int state=0;
Menu menu[5]={
	{"Calculation",11},
	{"Function",8},
	{"Equation",8},
	{"Complex",7},
	{"Definite",8}
};
List equalist[]={
{"quadratic",9},
{"cubic",5},
{"quartic",7},
{"solve",5}
};




#include <stdio.h>
/**
  * 函数功能: 重定向c库函数printf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}
 
/**
  * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
  return ch;
}
#define RXBUFFERSIZE  256
char RxBuffer[RXBUFFERSIZE];
uint8_t aRxBuffer;
uint8_t Uart1_Rx_Cnt = 0;
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	//HAL_UART_Receive_IT(&huart1, (uint8_t *) &aRxBuffer, 1);
//char str[100];

	//char ch[100];
	printf("nmsl");
  //HAL_UART_Transmit(&huart1, (uint8_t *)"7",1,0xFFFF);
	//OLED_ShowNum(50,3,23,2,16);
	//printf("nmsl");
	
	
	
	u8g2_t u8g2; // 显示器初始化结构体
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET); //复位拉高
  u8g2Init(&u8g2);  //显示器调用初始化函数
	u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
	u8g2_ClearBuffer(&u8g2);
	key_init();
	f_len=f_len_trg=list[ui_func_select].cnt*8;
	ef_len=ef_len_trg=list[ui_equa_select].cnt*8;

	//OLED_ShowString(0,3,str);
	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		u8g2_FirstPage(&u8g2);
       do
       {
				 switch(idx){
						 case 0:{
								show_main_menu(&u8g2);
								break;
						 }
						 case 1:{
							 show_calc_menu(&u8g2);
									break;
						 }
						 case 2:{
								show_func_menu(&u8g2);
							 //u8g2_DrawStr(&u8g2,64,50,"nmsl");
								break;
						 }
						 case 20:{
								show_sub0_menu(&u8g2);
							 break;
						 }
						 case 21:{
								show_sub1_menu(&u8g2);
							 break;
						 }
						 case 22:{
								show_sub2_menu(&u8g2);
							 break;
						 }
						 case 23:{
								show_sub3_menu(&u8g2);
							 break;
						 }
						 case 24:{
								show_sub4_menu(&u8g2);
							 break;
						 }
						 case 25:{
								show_sub5_menu(&u8g2);
							 break;
						 }
						 case 26:{
								show_sub6_menu(&u8g2);
							 break;
						 }
						 case 27:{
								show_sub7_menu(&u8g2);
							 break;
						 }
						 case 28:{
								show_sub8_menu(&u8g2);
							 break;
						 }
						 case 29:{
								show_sub9_menu(&u8g2);
							 break;
						 }
						 case 3:{
								show_equa_menu(&u8g2);
							 break;
						 }
						 case 32:{
									show_quad_calc(&u8g2);
							 break;
						 }
						 case 33:{
									show_cub_calc(&u8g2);
							 break;
						 }
						 case 34:{
									show_quar_calc(&u8g2);
							 break;
						 }
						 case 35:{
									show_func_solu(&u8g2);
							 break;
						 }
						 case 4:{
									show_comp_calc(&u8g2);
							 break;
						 }
						 case 5:{
									show_def_solu(&u8g2);
							 break;
						 }
				 }
				 
       } while (u8g2_NextPage(&u8g2));
		

		
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
