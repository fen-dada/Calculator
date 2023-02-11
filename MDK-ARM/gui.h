/*******************************************************************************
* 文件名称：md_oled_driver.h
*
* 摘	要：STM32F1的OLED中间驱动层头文件
*
* 当前版本：V1.0
* 作    者：yang_xi
* 日    期：2022/01/20
* 编译环境：keil_5

* 历史信息：
*******************************************************************************/
#ifndef __GUI_H
#define __GUI_H

#include "stdlib.h"	  
#include "main.h"
#include "gpio.h"
#include "u8g2.h"
#include "u8x8.h"
#include "stdio.h"
#include "keyboard.h"
#include "oled.h"
#include "calc.h"
#include "comp.h"
#include "value.h"
#include<stdbool.h>
//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x00
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF    //亮度
#define X_WIDTH 	128
#define Y_WIDTH 	64	
#define wkup HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)
#define key1 HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9)
#define key0 HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_8)
#define key2 HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)

extern int x,x_trg,y,y_trg,state;
extern int f_len,f_len_trg,f_y,f_y_trg,f_x,f_x_trg,f_h,f_h_trg;
extern int ui_func_select,ui_menu_select,ui_equa_select,equa_2_select,equa_3_select,equa_4_select;
extern int menu_x,menu_y,menu_x_trg,menu_y_trg;
extern int equa_x,equa_y,equa_x_trg,equa_y_trg;
extern int ef_x,ef_y,ef_y_trg,ef_x_trg,ef_len,ef_len_trg,ef_h,ef_h_trg;
extern bool legal;
extern int def_select;
typedef struct{
		char* title;
		int cnt;
}List;

typedef struct{
		int id;
		int press;
	 int is_update;
		int res;
}Key_msg;

typedef struct{
		char* title;
	int cnt;
}Menu;



typedef struct {
		int val,last_val;
}Key;

extern Key key[2];
extern List list[];
extern Key_msg key_msg;
extern Menu menu[5];
extern int idx;
extern List equalist[];
extern int key_state;





//-----------------OLED端口定义----------------  					   
#define MD_OLED_RST_Clr() HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_RESET) //oled 复位端口操作
#define MD_OLED_RST_Set() HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_SET)

//OLED控制用函数
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,void *arg_ptr);
uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,U8X8_UNUSED void *arg_ptr) ;
void u8g2Init(u8g2_t *u8g2);
void draw(u8g2_t *u8g2);

int gui_run(int* a,int* a_trg);
void key_init();
GPIO_TypeDef* Key_judge(int i);
uint16_t trans_pin(int i);
void show_func_menu(u8g2_t *u8g2);
int key_scan_ud();
int key_scan_lr();
void show_main_menu(u8g2_t *u8g2);
void show_calc_menu(u8g2_t *u8g2);
void show_equa_menu(u8g2_t *u8g2);
void show_quad_calc(u8g2_t *u8g2);
void show_cub_calc(u8g2_t *u8g2);
void show_quar_calc(u8g2_t *u8g2);
void show_comp_calc(u8g2_t *u8g2);
void show_sub0_menu(u8g2_t *u8g2);
void show_sub1_menu(u8g2_t *u8g2);
void show_sub2_menu(u8g2_t *u8g2);
void show_sub3_menu(u8g2_t *u8g2);
void show_sub4_menu(u8g2_t *u8g2);
void show_sub5_menu(u8g2_t *u8g2);
void show_sub6_menu(u8g2_t *u8g2);
void show_sub7_menu(u8g2_t *u8g2);
void show_sub8_menu(u8g2_t *u8g2);
void show_sub9_menu(u8g2_t *u8g2);
void show_func_solu(u8g2_t *u8g2);
void show_def_solu(u8g2_t *u8g2);

#endif  
/********************************* end_of_file **********************************/
