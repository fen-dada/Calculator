#include "main.h"
#include "keyboard.h"
//#include "usart.h"
//#include "gpio.h"
 
char MatrixKey()  //修改
{
		char KeyNumber=' ';  //储存按键值
		int cnt = 0; //长按计数
		
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2, GPIO_PIN_RESET); //  PB13 = 0 
//		HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET); //  PB12 = 1
//		HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_SET); //  PB15 = 1
//		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET); //  PB14 = 1
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0); HAL_Delay(15); KeyNumber = '/'; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); HAL_Delay(15); KeyNumber = '='; }	
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0); HAL_Delay(15); KeyNumber = '0'; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0); HAL_Delay(15); KeyNumber = 'c'; }
		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2, GPIO_PIN_SET); //  PB13 = 1 			
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_RESET); //  PB12 = 0
//		HAL_GPIO_WritePin(R3_GPIO_Port, R3_PinR3_PinR3_PinR3_Pin, GPIO_PIN_SET); //  PB15 = 1
//		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET); //  PB14 = 1
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0); HAL_Delay(15); KeyNumber = '*'; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); HAL_Delay(15); KeyNumber = '9'; }	
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0); HAL_Delay(15); KeyNumber = '8'; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0); HAL_Delay(15); KeyNumber = '7'; }			
			
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2, GPIO_PIN_RESET);   //PB13 = 1 			
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_SET); //  PB12 = 1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2, GPIO_PIN_RESET); //  PB15 = 0
//		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET); //  PB14 = 1
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0); HAL_Delay(15); KeyNumber = '-'; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); HAL_Delay(15); KeyNumber = '6'; }	
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0); HAL_Delay(15); KeyNumber = '5'; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0); HAL_Delay(15); KeyNumber = '4'; }
			
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2, GPIO_PIN_RESET); //  PB13 = 1 			
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_SET); //  PB12 = 1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2, GPIO_PIN_SET);//  PB15 = 1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3, GPIO_PIN_RESET); //  PB14 = 0
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0); HAL_Delay(15); KeyNumber = '+'; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); HAL_Delay(15); KeyNumber = '3'; }	
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0); HAL_Delay(15); KeyNumber = '2'; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0); HAL_Delay(15); KeyNumber = '1'; } //长按效果
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2, GPIO_PIN_RESET);  //  PB13 = 1 			
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_SET); //  PB12 = 1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2, GPIO_PIN_SET);//  PB15 = 1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3, GPIO_PIN_SET);
			
//			if(KeyNumber != 0)
//			{
//				printf("%d",KeyNumber);
//				KeyNumber = 0;
//			}	
	return KeyNumber;
}





char* MatrixKey_s(){
		char* s=" ";
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2, GPIO_PIN_RESET); //  PB13 = 0 
//		HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET); //  PB12 = 1
//		HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_SET); //  PB15 = 1
//		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET); //  PB14 = 1
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0); HAL_Delay(15); s = "/"; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); HAL_Delay(15); s = "="; }	
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0); HAL_Delay(15); s = "0"; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0); HAL_Delay(15); s = "="; }
		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2, GPIO_PIN_SET); //  PB13 = 1 			
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_RESET); //  PB12 = 0
//		HAL_GPIO_WritePin(R3_GPIO_Port, R3_PinR3_PinR3_PinR3_Pin, GPIO_PIN_SET); //  PB15 = 1
//		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET); //  PB14 = 1
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0); HAL_Delay(15); s = "*"; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); HAL_Delay(15); s = "9"; }	
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0); HAL_Delay(15); s = "8"; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0); HAL_Delay(15); s = "7"; }			
			
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2, GPIO_PIN_RESET);   //PB13 = 1 			
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_SET); //  PB12 = 1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2, GPIO_PIN_RESET); //  PB15 = 0
//		HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET); //  PB14 = 1
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0); HAL_Delay(15); s = "-"; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); HAL_Delay(15); s = "6"; }	
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0); HAL_Delay(15); s = "5"; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0); HAL_Delay(15); s = "4"; }
			
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2, GPIO_PIN_RESET); //  PB13 = 1 			
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_SET); //  PB12 = 1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2, GPIO_PIN_SET);//  PB15 = 1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3, GPIO_PIN_RESET); //  PB14 = 0
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0); HAL_Delay(15); s = "+"; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 0); HAL_Delay(15); s = "tan("; }	
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 0); HAL_Delay(15); s = "cos("; }
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0)
			{		HAL_Delay(20); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0); HAL_Delay(15); s = "sin("; } //长按效果
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2, GPIO_PIN_RESET);  //  PB13 = 1s
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1, GPIO_PIN_SET); //  PB12 = 1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2, GPIO_PIN_SET);//  PB15 = 1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3, GPIO_PIN_SET);
			
			
			return s;
}