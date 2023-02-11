/*******************************************************************************
* 文件名称：md_oled_driver.c
*
* 摘	要：STM32F1的OLED中间驱动层c文件
*
* 当前版本：V1.0
* 作    者：yang_xi
* 日    期：2022/01/20
* 编译环境：keil_5

* 历史信息：
*******************************************************************************/
//----------------------------------------------------------------
//GND    电源地
//VCC  接5V或3.3v电源
//D0   接PA5（SCL）
//D1   接PA7（SDA）
//RES  接PB0
//DC   接PB1
//CS   接PA4              
//----------------------------------------------------------------

//******************************************************************************/

#include "gui.h"
#include "stdlib.h"
//#include "md_oled_font.h"
#include "spi.h"
#include "u8g2.h"
#include "u8x8.h"
#include "calc.h"

int d_y=20,d_y_trg=20;
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,void *arg_ptr)
{
    switch (msg)
    {
        case U8X8_MSG_BYTE_SEND: /*通过SPI发送arg_int个字节数据*/
			HAL_SPI_Transmit(&hspi1,(uint8_t *)arg_ptr,arg_int,200);
            break;
        case U8X8_MSG_BYTE_INIT: /*初始化函数*/
            break;
        case U8X8_MSG_BYTE_SET_DC: /*设置DC引脚,表明发送的是数据还是命令*/
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,arg_int);
            break;
        case U8X8_MSG_BYTE_START_TRANSFER: 
            break;
        case U8X8_MSG_BYTE_END_TRANSFER: 
            break;
        default:
            return 0;
    }
    return 1;
}

uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,
    U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
    U8X8_UNUSED void *arg_ptr) 
{
    switch (msg)
    {
        case U8X8_MSG_GPIO_AND_DELAY_INIT: /*delay和GPIO的初始化，在main中已经初始化完成了*/
            break;
        case U8X8_MSG_DELAY_MILLI: /*延时函数*/
            HAL_Delay(arg_int);     //调用谁stm32系统延时函数
            break;
        case U8X8_MSG_GPIO_CS: /*片选信号*/ //由于只有一个SPI设备，所以片选信号在初始化时已经设置为为常有效
            break;
        case U8X8_MSG_GPIO_DC: /*设置DC引脚,表明发送的是数据还是命令*/
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,arg_int);
            break;
        case U8X8_MSG_GPIO_RESET:
            break;
    }
    return 1;
}

void u8g2Init(u8g2_t *u8g2)
{
	
/********************************************     
U8G2_R0     //不旋转，不镜像     
U8G2_R1     //旋转90度
U8G2_R2     //旋转180度   
U8G2_R3     //旋转270度
U8G2_MIRROR   //没有旋转，横向显示左右镜像
U8G2_MIRROR_VERTICAL    //没有旋转，竖向显示镜像
********************************************/
//    u8g2_Setup_sh1106_128x64_noname_2(u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay);  // 初始化1.3寸OLED u8g2 结构体
	u8g2_Setup_ssd1306_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay);  // 初始化0.96寸OLED u8g2 结构体
	u8g2_InitDisplay(u8g2);     //初始化显示
	u8g2_SetPowerSave(u8g2, 0); //开启显示
}

void draw(u8g2_t *u8g2)
{
    u8g2_DrawLine(u8g2, 0, 0, 127, 0);  //画直线
    u8g2_DrawLine(u8g2, 0, 0, 0, 63);
    u8g2_DrawLine(u8g2, 0, 63, 127, 63);    
    u8g2_DrawLine(u8g2, 127, 0, 127, 63);
    
    u8g2_DrawLine(u8g2, 0, 0, 127, 63); //画直线
    u8g2_DrawLine(u8g2, 0, 63, 127, 0);

    u8g2_DrawPixel(u8g2, 115, 32); //画点
    u8g2_DrawBox(u8g2,56,44,14,10);   //画实心矩形
    u8g2_DrawCircle(u8g2,62,13,10,U8G2_DRAW_ALL); //画空心矩形
    u8g2_DrawFrame(u8g2,5,24,18,16);  //画空心圆形

    u8g2_SetFont(u8g2, u8g2_font_6x12_tf);  //设定字体
    u8g2_DrawStr(u8g2, 80,36,"YYDS");    //显示字符
}



GPIO_TypeDef* Key_judge(int i){
		if(i==0) return GPIOA;
		else if(i==1  || i==2) return GPIOC;
		else return GPIOD;
}

uint16_t trans_pin(int i){
		switch(i){
			case 0:{
				return 0;
				break;
			}
			case 1:{
				return 9;
				break;
			}
			case 2:{
				return 8;
				break;
			}
			case 3:{
				return 2;
				break;
			}
		}
}


int gui_run(int* a,int* a_trg)
{
	
	if(*a > *a_trg){
		*a-=1;
	}
	else if(*a < *a_trg){
		*a+=1;
	}
	else return 0;
	return 1;
	
	
}

void key_init(){
		for(int i=0;i<2;i++){
				key[i].val = key[i].last_val = HAL_GPIO_ReadPin(Key_judge(i),trans_pin(i));
		}
}

int a=0,b=0,c=0,d=0;

int key_scan_lr(){
	
		if(key0 == 0){
				HAL_Delay(5);
			b=!b;
				while(key0 == 0);
			  HAL_Delay(5);
				menu_x_trg+=128;
			if(idx==0) ui_menu_select--; 
			ui_menu_select=ui_menu_select<0 ? 0 : ui_menu_select;
			//menu_x_trg=menu_x_trg
			
		}
		else if(key2 == 0){
				HAL_Delay(5);
			d=!d;
				while(key2 == 0);
			  HAL_Delay(5);
				menu_x_trg-=128;
			if(idx==0) ui_menu_select++; 
			ui_menu_select=ui_menu_select>4 ? 4 : ui_menu_select;
			
		}
		
		
}


int key_scan_ud(){
		if(wkup == 1){
				HAL_Delay(5);
			  a=!a;
				while(wkup == 1);
			  HAL_Delay(5);
				
			if(idx==2){
				if(ui_func_select>0 && f_y_trg==1){
						y_trg+=10;
						f_y_trg+=10;
				}
					f_y_trg-=10;
					ui_func_select--;
				  f_y_trg=f_y_trg<0 ? 0 : f_y_trg;
			}else if(idx==3){
					ui_equa_select--;
						ef_y_trg-=10;
				ef_y_trg=ef_y_trg<0 ? 0 : ef_y_trg;
			}else if(idx==32){
					equa_2_select--;
				equa_2_select=equa_2_select<0?2:equa_2_select;
			}else if(idx==33){
					equa_3_select--;
				equa_3_select=equa_3_select<0?3:equa_3_select;
			}else if(idx==34){
					equa_4_select--;
				equa_4_select=equa_4_select<0?4:equa_4_select;
			}else if(idx==26||idx==29){
					d_y_trg-=10;
					if(d_y_trg<20) d_y_trg=30;
			}else if(idx==5){
					def_select--;
				def_select=def_select<0?2:def_select;
			}
		
			
		}
		else if(key1 == 0){
				HAL_Delay(5);
			c=!c;
				while(key1 == 0);
			  HAL_Delay(5);

			if(idx==2){
				f_y_trg+=10;
				if(ui_func_select<9 && f_y_trg==61){
						y_trg-=10;
						f_y_trg-=10;
				}
				else if(ui_func_select==9 && f_y_trg==61){
						y_trg=10;
						f_y_trg=1;
				}
				
					ui_func_select++; 
					//ui_func_select=ui_func_select>2 ? 2 : ui_func_select;
					ui_func_select%=10;
					//f_y_trg=f_y_trg>50 ? 50 : f_y_trg;
					f_y_trg%=62;
				
			}else if(idx==3){
					ui_equa_select++;
						ef_y_trg+=10;
				ef_y_trg=ef_y_trg>30 ? 30 : ef_y_trg;
				ui_equa_select=ui_equa_select>3?3:ui_equa_select;
			}else if(idx==32){
					equa_2_select++;
				equa_2_select%=3;
			}else if(idx==33){
					equa_3_select++;
				equa_3_select%=4;
			}else if(idx==34){
					equa_4_select++;
				equa_4_select%=5;
			}else if(idx==26||idx==29){
					d_y_trg+=10;
					if(d_y_trg>30) d_y_trg=20;
			}else if(idx==5){
					def_select++;
					def_select%=3;
			}
		}
		
}



void show_func_menu(u8g2_t *u8g2){

		key_scan_ud();
	  
		
		for(int i=0;i<10;i++){
				u8g2_DrawStr(u8g2,x+1,y+i*10,list[i].title);
		}
		u8g2_DrawRFrame(u8g2,f_x,f_y+1,f_len,11,1);
	  gui_run(&y,&y_trg);
		if(f_y<0) f_y=0;
		gui_run(&f_len,&f_len_trg);
		gui_run(&f_y,&f_y_trg);
		gui_run(&f_x,&f_x_trg);
		
		f_len_trg=list[ui_func_select>=0?ui_func_select:0].cnt*7;
		if(ui_func_select==-1){
				y_trg=128;
			f_y_trg=127;
			menu_y_trg=20;
			ui_func_select=0;
		}
		if(y==128){
			
				idx=0;
			
		}
		
		if(key2==0){
				HAL_Delay(5);
				idx=20+ui_func_select;
			while(key2==0);
		}


}

void show_main_menu(u8g2_t *u8g2){
		//u8g2_ClearBuffer(u8g2);
	  key_scan_lr();
	
	  for(int i=0;i<5;i++){
		  u8g2_DrawStr(u8g2,menu_x+64-menu[ui_menu_select].cnt*3+i*128,menu_y,menu[i].title);
	  }
		
	  if(menu_x<-4*128) menu_x=-4*128,menu_x_trg=-4*128;
		if(menu_x>0) menu_x=0,menu_x_trg=0;
		gui_run(&menu_x,&menu_x_trg);
	  gui_run(&menu_y,&menu_y_trg);
		if(key1 == 0){
				HAL_Delay(5);
			
				menu_y_trg=-64;
			
				while(key1 == 0);
			
				HAL_Delay(5);
			
		}
		if(menu_y==-64){
				
		
			y_trg=10;
			f_y_trg=1;
			ef_y_trg=1;
			equa_y_trg=10;
				
				idx=ui_menu_select+1;
		}
}


char str[100];
char res[100];
int cnt=0;


char temp[100];
char next[100];
char third[100];
extern bool legal;
bool is_first=true;


void show_calc_menu(u8g2_t *u8g2){
	if(legal==false){
			memset(res,0,sizeof(res));
			u8g2_DrawStr(u8g2,50,50,"Input error");
	}
	static int i,next_i,third_i=0;
		u8g2_DrawStr(u8g2,0,10,"->");
		char aRx=MatrixKey();
	
	 u8g2_DrawStr(u8g2,10,10,str);
	u8g2_DrawStr(u8g2,0,20,next);
	u8g2_DrawStr(u8g2,0,30,third);
	if(legal) u8g2_DrawStr(u8g2,50,50,res);
	//u8g2_SendBuffer(u8g2);
	if(aRx!='=' && aRx!='c'&&aRx!=' '){
			if(is_first){
					memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				memset(next, 0, sizeof(res));
				memset(third, 0, sizeof(res));
					is_first=false;
				legal=true;
			}
		}
	switch(aRx){
				case '1':{
						if(key_state) strcat(str,"sin(");
					else strcat(str,"1");
					break;
				}
				case '2':{
						if(key_state) strcat(str,"cos(");
					else strcat(str,"2");
					break;
				}
				case '3':{
						if(key_state) strcat(str,"tan(");
					else strcat(str,"3");
					break;
				}
				case '+':{
						if(!key_state) strcat(str,"+");
					else strcat(str,"log");
					break;
				}
				case '4':{
						if(key_state) strcat(str,"arcsin(");
					else strcat(str,"4");
					break;
				}
				case '5':{
						if(key_state) strcat(str,"arccos(");
					else strcat(str,"5");
					break;
				}
				case '6':{
						if(key_state) strcat(str,"arctan(");
					else strcat(str,"6");
					break;
				}
				case'-':{
						if(!key_state) strcat(str,"-");
					else strcat(str,"ln(");
					break;
				}
				case'7':{
						if(!key_state) strcat(str,"7");
						else strcat(str,"(");
					break;
				}
				case'8':{
						if(!key_state) strcat(str,"8");
					else strcat(str,"^");
					break;
				}
				case'9':{
						if(!key_state) strcat(str,"9");
						else strcat(str,")");
					break;
				}
				case'*':{
						if(!key_state) strcat(str,"*");
					else strcat(str,"e");
					break;
				}
				case'/':{
						if(!key_state) strcat(str,"/");
					else strcat(str,"pi");
					break;
				}
				case'0':{
						if(!key_state) strcat(str,"0");
					else strcat(str,"!");
					break;
				}
				
			}
			
		
			//u8g2_ClearBuffer(u8g2);
			//strcat(str,&aRx);
			
			//str[i++]=aRx;
			/*
			int l=strlen(str);
			if(strlen(str)>21&&l<=42){
					next[next_i++]=aRx;
				//strcat(next,)
			}else if(l>42){
					third[third_i++]=aRx;
			}
			*/
			
		
		 if(aRx=='='){
			
				 double ans=calc(str);
				/*
			if(!legal){
				
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			}else{
			*/
			 
			 if(isnan(ans)){
				 memset(res, 0, sizeof(res));
					legal=false;
			 }else{
					memset(res, 0, sizeof(res));
				  sprintf(res,"%.4lf",ans);
			 }
				
				
				
				//u8g2_DrawStr(u8g2,50,50,res);

				is_first=true;
				i=0;
				next_i=0;
				third_i=0;
			//}
				
		}
		else if(aRx=='c'){
			//OLED_Clear();
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			memset(next, 0, sizeof(res));
			memset(third, 0, sizeof(res));
			i=0;
			next_i=0;
			third_i=0;
			legal=true;
		}
		
		if(wkup == 1){
		
				HAL_Delay(5);
			menu_y_trg=20;
			idx=0;
			memset(str, 0, sizeof(str));
			memset(res, 0, sizeof(res));
			memset(next, 0, sizeof(res));
			memset(third, 0, sizeof(res));
			while(wkup==1);
			HAL_Delay(5);
		}
		else if(key1==0){
			HAL_Delay(5);
				//str[i++]='^';
			
			
			key_state=!key_state;
			
			while(key1==0);
		
		}else if(key0==0){
			HAL_Delay(5);
				//str[i++]='(';
			if(is_first){
					memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				memset(next, 0, sizeof(res));
				memset(third, 0, sizeof(res));
					is_first=false;
				legal=true;
			}
			strcat(str,".");
			while(key0==0);
		
		}else if(key2==0){
			HAL_Delay(5);
				//str[i++]=')';
				strcat(str,")");
			while(key2==0);
		
		}
}

void show_equa_menu(u8g2_t *u8g2){
		key_scan_ud();
		for(int i=0;i<4;i++){
		
				u8g2_DrawStr(u8g2,equa_x+3,equa_y+i*10,equalist[i].title);
		
		}
		
		u8g2_DrawRFrame(u8g2,ef_x,ef_y+1,ef_len,11,1);
	  gui_run(&equa_y,&equa_y_trg);
		//if(f_y<0) f_y=0;
		gui_run(&ef_len,&ef_len_trg);
		gui_run(&ef_y,&ef_y_trg);
		gui_run(&ef_x,&ef_x_trg);
		
		ef_len_trg=equalist[ui_equa_select>=0?ui_equa_select:0].cnt*7;
		
		if(ui_equa_select==-1){
				equa_y_trg=128;
			ef_y_trg=127;
			menu_y_trg=20;
			ui_equa_select=0;
		}
		if(equa_y==128){
			
				idx=0;
			
		}
		if(key2 == 0){
		
				HAL_Delay(5);
			
		  idx=30+ui_equa_select+2;
			while(key2==0);
			HAL_Delay(5);
		}
}


char av[100];
char bv[100];
char cv[100];
char dv[100];
char ev[100];
char c_ans[100];
bool e_first=true;;
int a_idx=0,b_idx=0,c_idx=0,d_idx=0,e_idx=0;
int a_y,a_y_trg;
int e=2;



void show_quad_calc(u8g2_t *u8g2){
	u8g2_DrawStr(u8g2,1,60,c_ans);	
		key_scan_ud();
		a_y_trg=10*(equa_2_select+2);
		u8g2_DrawStr(u8g2,1,10,"ax^2 + bx + c = 0");
	u8g2_DrawStr(u8g2,1,a_y,"->");
	u8g2_DrawStr(u8g2,14,20,"a:");
	u8g2_DrawStr(u8g2,14,30,"b:");
	u8g2_DrawStr(u8g2,14,40,"c:");
	u8g2_DrawStr(u8g2,25,20,av);
	u8g2_DrawStr(u8g2,25,30,bv);
	u8g2_DrawStr(u8g2,25,40,cv);
	gui_run(&a_y,&a_y_trg);
		char c = MatrixKey();
			if(c!=' '&& c!='='&& c!='c'){
				if(e_first){
						equa_2_select=0;
						a_idx=0;
						b_idx=0;
						c_idx=0;
						memset(av,0,sizeof(av));
						memset(bv,0,sizeof(bv));
						memset(cv,0,sizeof(cv));
					  memset(c_ans,0,sizeof(c_ans));
						e_first=false;
				}
				
					if(a_y_trg==20){
							av[a_idx++]=c;
						
					}else if(a_y_trg==30){
							bv[b_idx++]=c;
					}else if(a_y_trg==40){
							cv[c_idx++]=c;
					}
			
			}else if(c=='='){
				char* end;
				char temp[100];
					double a,b,c;
					a=strtod(av,&end);
					b=strtod(bv,&end);
					c=strtod(cv,&end);
					double prin=b*b-4*a*c;
					if(prin>0){
							strcat(c_ans,"x1=");
							double x1=(-b-sqrt(prin))/(2*a);
							double x2=(-b+sqrt(prin))/(2*a);
							
							sprintf(temp,"%.4lf",x1);
							strcat(c_ans,temp);
							memset(temp,0,sizeof(temp));
							strcat(c_ans,",");
							strcat(c_ans,"x2=");
							sprintf(temp,"%.4lf",x2);
							strcat(c_ans,temp);
					}else if(prin==0){
							double x1=(-b)/(2*a);
							strcat(c_ans,"x1=x2=");
							sprintf(temp,"%.4lf",x1);
							strcat(c_ans,temp);
					}else{
							strcat(c_ans,"No real solution");
					}
					
				
					
				e_first=true;
			}else if(c=='c'){
					a_idx=0;
				b_idx=0;
				c_idx=0;
				memset(av,0,sizeof(av));
				memset(bv,0,sizeof(bv));
				memset(cv,0,sizeof(cv));
				memset(c_ans,0,sizeof(c_ans));
				equa_2_select=0;
				
			}
				
				if(key0==0){
						HAL_Delay(5);
					idx=3;
					ef_x_trg=0;
					memset(av,0,sizeof(av));
				memset(bv,0,sizeof(bv));
				memset(cv,0,sizeof(cv));
				memset(dv,0,sizeof(cv));
					memset(ev,0,sizeof(ev));
					memset(c_ans,0,sizeof(c_ans));
					while(key0==0);
					
				}
}


int b_y,b_y_trg;

void show_cub_calc(u8g2_t *u8g2){

		u8g2_DrawStr(u8g2,60,60,c_ans);
	  key_scan_ud();
	b_y_trg=10*(equa_3_select+2);
	u8g2_DrawStr(u8g2,1,10,"ax^3+bx^2+cx+d=0");
	u8g2_DrawStr(u8g2,1,b_y,"->");
	u8g2_DrawStr(u8g2,14,20,"a:");
	u8g2_DrawStr(u8g2,14,30,"b:");
	u8g2_DrawStr(u8g2,14,40,"c:");
	u8g2_DrawStr(u8g2,14,50,"d:");
	u8g2_DrawStr(u8g2,25,20,av);
	u8g2_DrawStr(u8g2,25,30,bv);
	u8g2_DrawStr(u8g2,25,40,cv);
	u8g2_DrawStr(u8g2,25,50,dv);
	gui_run(&b_y,&b_y_trg);
	char c = MatrixKey();
			if(c!=' '&& c!='='&& c!='c'){
				if(e_first){
						//a_y=30;
					b_y_trg=20;
					equa_3_select=0;
						a_idx=0;
						b_idx=0;
						c_idx=0;
					  d_idx=0;
						memset(av,0,sizeof(av));
						memset(bv,0,sizeof(bv));
						memset(cv,0,sizeof(cv));
					  memset(dv,0,sizeof(dv));
					  memset(c_ans,0,sizeof(c_ans));
						e_first=false;
				}
				
					if(b_y_trg==20){
							av[a_idx++]=c;
						
					}else if(b_y_trg==30){
							bv[b_idx++]=c;
					}else if(b_y_trg==40){
							cv[c_idx++]=c;
					}else if(b_y_trg==50){
							dv[d_idx++]=c;
					}
			
			}else if(c=='='){
				char* end;
					double a,b,c,d;
					a=strtod(av,&end);
					b=strtod(bv,&end);
					c=strtod(cv,&end);
					d=strtod(dv,&end);
					double ans=solve_3(a,b,c,d);
					sprintf(c_ans,"%lf",ans);
				
					
				e_first=true;
			}else if(c=='c'){
					a_idx=0;
				b_idx=0;
				c_idx=0;
				d_idx=0;
				memset(av,0,sizeof(av));
				memset(bv,0,sizeof(bv));
				memset(cv,0,sizeof(cv));
				memset(dv,0,sizeof(cv));
				memset(c_ans,0,sizeof(c_ans));
				b_y_trg=20;
				equa_3_select=0;
			}
			
			if(key0==0){
			HAL_Delay(5);
					idx=3;
					ef_x_trg=0;
					memset(av,0,sizeof(av));
					memset(bv,0,sizeof(bv));
					memset(cv,0,sizeof(cv));
					memset(dv,0,sizeof(cv));
					memset(c_ans,0,sizeof(c_ans));
					while(key0==0);
					
				}
}

int c_y,c_y_trg;

void show_quar_calc(u8g2_t *u8g2){
		u8g2_DrawStr(u8g2,60,60,c_ans);
	  key_scan_ud();
	c_y_trg=10*(equa_4_select+2);
	u8g2_DrawStr(u8g2,1,10,"ax^4+bx^3+cx^2+dx+e=0");
	u8g2_DrawStr(u8g2,1,c_y,"->");
	u8g2_DrawStr(u8g2,14,20,"a:");
	u8g2_DrawStr(u8g2,14,30,"b:");
	u8g2_DrawStr(u8g2,14,40,"c:");
	u8g2_DrawStr(u8g2,14,50,"d:");
	u8g2_DrawStr(u8g2,14,60,"e:");
	u8g2_DrawStr(u8g2,25,20,av);
	u8g2_DrawStr(u8g2,25,30,bv);
	u8g2_DrawStr(u8g2,25,40,cv);
	u8g2_DrawStr(u8g2,25,50,dv);
	u8g2_DrawStr(u8g2,25,60,ev);
	gui_run(&c_y,&c_y_trg);
	
	char c = MatrixKey();
			if(c!=' '&& c!='='&& c!='c'){
				if(e_first){
						//a_y=30;
					c_y_trg=20;
					equa_4_select=0;
						a_idx=0;
						b_idx=0;
						c_idx=0;
					  d_idx=0;
					  e_idx=0;
						memset(av,0,sizeof(av));
						memset(bv,0,sizeof(bv));
						memset(cv,0,sizeof(cv));
					  memset(dv,0,sizeof(dv));
					memset(ev,0,sizeof(ev));
					  memset(c_ans,0,sizeof(c_ans));
						e_first=false;
				}
				
					if(c_y_trg==20){
							av[a_idx++]=c;
						
					}else if(c_y_trg==30){
							bv[b_idx++]=c;
					}else if(c_y_trg==40){
							cv[c_idx++]=c;
					}else if(c_y_trg==50){
							dv[d_idx++]=c;
					}else if(c_y_trg==60){
							ev[e_idx++]=c;
					}
			
			}else if(c=='='){
				char* end;
					double a,b,c,d,e;
					a=strtod(av,&end);
					b=strtod(bv,&end);
					c=strtod(cv,&end);
					d=strtod(dv,&end);
				  e=strtod(ev,&end);
					double ans=solve_4(a,b,c,d,e);
					sprintf(c_ans,"%lf",ans);
				
					
				e_first=true;
			}else if(c=='c'){
					a_idx=0;
				b_idx=0;
				c_idx=0;
				d_idx=0;
				e_idx=0;
				memset(av,0,sizeof(av));
				memset(bv,0,sizeof(bv));
				memset(cv,0,sizeof(cv));
				memset(dv,0,sizeof(dv));
				memset(ev,0,sizeof(ev));
				memset(c_ans,0,sizeof(c_ans));
				c_y_trg=20;
				equa_4_select=0;
			}
			
			if(key0==0){
						HAL_Delay(5);
					idx=3;
					ef_x_trg=0;
					memset(av,0,sizeof(av));
				memset(bv,0,sizeof(bv));
				memset(cv,0,sizeof(cv));
				memset(dv,0,sizeof(cv));
				memset(ev,0,sizeof(ev));
				memset(c_ans,0,sizeof(c_ans));
					while(key0==0);
					
				}
}

char res_i[100];

void show_comp_calc(u8g2_t* u8g2){
		Comp ans;
		static int i=0;
		u8g2_DrawStr(u8g2,0,10,"->");
		char aRx=MatrixKey();
	  u8g2_DrawStr(u8g2,12,10,str);
	  u8g2_DrawStr(u8g2,10,50,res);

			if(aRx!='=' && aRx!='c'&&aRx!=' '){
			 


			if(is_first){
					memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				memset(res_i, 0, sizeof(res_i));
				u8g2_ClearBuffer(u8g2);
					is_first=false;
				ans.imag=0;
				ans.real=0;
			}
			//u8g2_ClearBuffer(u8g2);
			//strcat(str,&aRx);
			
			str[i++]=aRx;
			
		}
		else if(aRx=='='){
					ans.imag=0;
				ans.real=0;
				 ans=comp_calc(str);
				/*
			if(!legal){
				
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			}else{
			*/
				memset(res, 0, sizeof(res));
			memset(res_i, 0, sizeof(res));
				sprintf(res,"%.2lf",ans.real);
				if(ans.imag>=0){
							strcat(res,"+");
				}
				
			  sprintf(res_i,"%.2lf",ans.imag);
				strcat(res_i,"i");
				strcat(res,res_i);

				is_first=true;
				i=0;
				u8g2_ClearBuffer(u8g2);
				ans.imag=0;
				ans.real=0;
			//}
				
		}
		else if(aRx=='c'){

			i=0;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			memset(res_i, 0, sizeof(res_i));
			is_first=true;
			u8g2_ClearBuffer(u8g2);
			ans.imag=0;
				ans.real=0;
		}
		
		if(wkup == 1){
		
				HAL_Delay(5);
			menu_y_trg=20;
			idx=0;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			memset(res_i, 0, sizeof(res));
			ans.imag=0;
				ans.real=0;
			u8g2_ClearBuffer(u8g2);
			i=0;
			while(wkup==1);
			HAL_Delay(5);
		}
		else if(key1==0){
			HAL_Delay(5);
			if(is_first){
					memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				memset(res_i, 0, sizeof(res_i));
	
					is_first=false;
			}
				str[i++]='i';
			
			is_first=false;
			while(key1==0);
		
		}else if(key0==0){
			HAL_Delay(5);
			if(is_first){
					memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				memset(res_i, 0, sizeof(res_i));
			
					is_first=false;
			}
				str[i++]='(';
			
			is_first=false;
			while(key0==0);
		
		}else if(key2==0){
			HAL_Delay(5);
			if(is_first){
					memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				memset(res_i, 0, sizeof(res_i));
			
					is_first=false;
			 }
				str[i++]=')';
			
			is_first=false;
			while(key2==0);
		
		}
}

void show_sub0_menu(u8g2_t *u8g2){
	
	static int i=0;
				u8g2_DrawStr(u8g2,50,50,res);
				u8g2_DrawStr(u8g2,1,20,"->");
	      u8g2_DrawStr(u8g2,14,20,"x:");
				u8g2_DrawStr(u8g2,25,20,str);
	      u8g2_DrawStr(u8g2,1,10,"sinx");
	

				char aRx=MatrixKey();
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
						if(is_first){
							memset(str, 0, sizeof(str));
						memset(res, 0, sizeof(res));
							is_first=false;
					  }
						str[i++]=aRx;
			}else if(aRx=='='){
				  char* t;
	       double x = strtod(str,&t);
				 double ans=sin(x);
					sprintf(res,"%.2lf",ans);
					is_first=true;
				i=0;
			}else if(aRx=='c'){
					i=0;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			
			is_first=true;
			}
			
			
			
			if(key0==0){
					HAL_Delay(5);
					idx=2;
					//ef_x_trg=0;
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				while(key0==0);
			}
				
}

void show_sub1_menu(u8g2_t *u8g2){
	
	static int i=0;
				u8g2_DrawStr(u8g2,50,50,res);
				u8g2_DrawStr(u8g2,1,20,"->");
	      u8g2_DrawStr(u8g2,14,20,"x:");
				u8g2_DrawStr(u8g2,25,20,str);
	      u8g2_DrawStr(u8g2,1,10,"cosx");
	

				char aRx=MatrixKey();
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
						if(is_first){
							memset(str, 0, sizeof(str));
						memset(res, 0, sizeof(res));
							is_first=false;
					  }
						str[i++]=aRx;
			}else if(aRx=='='){
				  char* t;
	       double x = strtod(str,&t);
				 double ans=cos(x);
					sprintf(res,"%.2lf",ans);
					is_first=true;
				i=0;
			}else if(aRx=='c'){
					i=0;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			
			is_first=true;
			}
			
			
			
			if(key0==0){
					HAL_Delay(5);
					idx=2;
					//ef_x_trg=0;
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				while(key0==0);
			}
				
}

void show_sub2_menu(u8g2_t *u8g2){
	
	static int i=0;
				u8g2_DrawStr(u8g2,50,50,res);
				u8g2_DrawStr(u8g2,1,20,"->");
	      u8g2_DrawStr(u8g2,14,20,"x:");
				u8g2_DrawStr(u8g2,25,20,str);
	      u8g2_DrawStr(u8g2,1,10,"tanx");
	

				char aRx=MatrixKey();
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
						if(is_first){
							memset(str, 0, sizeof(str));
						memset(res, 0, sizeof(res));
							is_first=false;
					  }
						str[i++]=aRx;
			}else if(aRx=='='){
				  char* t;
	       double x = strtod(str,&t);
				 double ans=tan(x);
					sprintf(res,"%.2lf",ans);
					is_first=true;
				i=0;
			}else if(aRx=='c'){
					i=0;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			
			is_first=true;
			}
			
			
			
			if(key0==0){
					HAL_Delay(5);
					idx=2;
					//ef_x_trg=0;
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				while(key0==0);
			}
				
}

void show_sub3_menu(u8g2_t *u8g2){
	
	static int i=0;
				u8g2_DrawStr(u8g2,50,50,res);
				u8g2_DrawStr(u8g2,1,20,"->");
	      u8g2_DrawStr(u8g2,14,20,"x:");
				u8g2_DrawStr(u8g2,25,20,str);
	      u8g2_DrawStr(u8g2,1,10,"arcsinx");
	

				char aRx=MatrixKey();
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
						if(is_first){
							memset(str, 0, sizeof(str));
						memset(res, 0, sizeof(res));
							is_first=false;
					  }
						str[i++]=aRx;
			}else if(aRx=='='){
				  char* t;
	       double x = strtod(str,&t);
				 double ans=asin(x);
					sprintf(res,"%.2lf",ans);
					is_first=true;
				i=0;
			}else if(aRx=='c'){
					i=0;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			
			is_first=true;
			}
			
			
			
			if(key0==0){
					HAL_Delay(5);
					idx=2;
					//ef_x_trg=0;
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				while(key0==0);
			}
				
}



void show_sub4_menu(u8g2_t *u8g2){
	
	static int i=0;
				u8g2_DrawStr(u8g2,50,50,res);
				u8g2_DrawStr(u8g2,1,20,"->");
	      u8g2_DrawStr(u8g2,14,20,"x:");
				u8g2_DrawStr(u8g2,25,20,str);
	      u8g2_DrawStr(u8g2,1,10,"arccosx");
	

				char aRx=MatrixKey();
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
						if(is_first){
							memset(str, 0, sizeof(str));
						memset(res, 0, sizeof(res));
							is_first=false;
					  }
						str[i++]=aRx;
			}else if(aRx=='='){
				  char* t;
	       double x = strtod(str,&t);
				 double ans=acos(x);
					sprintf(res,"%.2lf",ans);
					is_first=true;
				i=0;
			}else if(aRx=='c'){
					i=0;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			
			is_first=true;
			}
			
			
			
			if(key0==0){
					HAL_Delay(5);
					idx=2;
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				while(key0==0);
			}
				
}




void show_sub5_menu(u8g2_t *u8g2){
	
	static int i=0;
				u8g2_DrawStr(u8g2,50,50,res);
				u8g2_DrawStr(u8g2,1,20,"->");
	      u8g2_DrawStr(u8g2,14,20,"x:");
				u8g2_DrawStr(u8g2,25,20,str);
	      u8g2_DrawStr(u8g2,1,10,"arctanx");
	

				char aRx=MatrixKey();
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
						if(is_first){
							memset(str, 0, sizeof(str));
						memset(res, 0, sizeof(res));
							is_first=false;
					  }
						str[i++]=aRx;
			}else if(aRx=='='){
				  char* t;
	       double x = strtod(str,&t);
				 double ans=atan(x);
					sprintf(res,"%.2lf",ans);
					is_first=true;
				i=0;
			}else if(aRx=='c'){
					i=0;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			
			is_first=true;
			}
			
			
			
			if(key0==0){
					HAL_Delay(5);
					idx=2;
					//ef_x_trg=0;
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				while(key0==0);
			}
				
}




void show_sub6_menu(u8g2_t *u8g2){
	key_scan_ud();
	static int i=0;
				u8g2_DrawStr(u8g2,50,50,res);
				u8g2_DrawStr(u8g2,1,d_y,"->");
	      u8g2_DrawStr(u8g2,14,20,"x:");
				u8g2_DrawStr(u8g2,14,30,"a:");
				u8g2_DrawStr(u8g2,25,20,str);
	      u8g2_DrawStr(u8g2,25,30,av);
	      u8g2_DrawStr(u8g2,1,10,"log");
				gui_run(&d_y,&d_y_trg);

				char aRx=MatrixKey();
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
						if(is_first){
							memset(str, 0, sizeof(str));
						memset(res, 0, sizeof(res));
							memset(av, 0, sizeof(res));
							is_first=false;
					  }
						if(d_y==20) str[i++]=aRx;
						if(d_y==30) av[a_idx++]=aRx;
			}else if(aRx=='='){
				  char* t;
	       double x = strtod(str,&t);
					double a = strtod(av,&t);
				 double ans=log_v(x,a);
					sprintf(res,"%.2lf",ans);
					is_first=true;
				i=0;
			}else if(aRx=='c'){
					i=0;
				a_idx=0;
				d_y_trg=20;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				memset(av, 0, sizeof(av));
			
			is_first=true;
			}
			
			
			
			if(key0==0){
					HAL_Delay(5);
					idx=2;
				d_y_trg=20;
					//ef_x_trg=0;
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				memset(av, 0, sizeof(res));
				while(key0==0);
			}
				
}

void show_sub7_menu(u8g2_t *u8g2){
	
	static int i=0;
				u8g2_DrawStr(u8g2,50,50,res);
				u8g2_DrawStr(u8g2,1,20,"->");
	      u8g2_DrawStr(u8g2,14,20,"x:");
				
				u8g2_DrawStr(u8g2,25,20,str);
	      u8g2_DrawStr(u8g2,1,10,"ln");
	

				char aRx=MatrixKey();
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
						if(is_first){
							memset(str, 0, sizeof(str));
						memset(res, 0, sizeof(res));
							is_first=false;
					  }
						str[i++]=aRx;
			}else if(aRx=='='){
				  char* t;
	       double x = strtod(str,&t);
				 double ans=log(x);
					sprintf(res,"%.2lf",ans);
					is_first=true;
				i=0;
			}else if(aRx=='c'){
					i=0;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			
			is_first=true;
			}

			if(key0==0){
					HAL_Delay(5);
					idx=2;
					//ef_x_trg=0;
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				while(key0==0);
			}
				
}

void show_sub8_menu(u8g2_t *u8g2){
	
	static int i=0;
				u8g2_DrawStr(u8g2,50,50,res);
				u8g2_DrawStr(u8g2,1,20,"->");
	      u8g2_DrawStr(u8g2,14,20,"x:");
				
				u8g2_DrawStr(u8g2,25,20,str);
	      u8g2_DrawStr(u8g2,1,10,"e^x");
	

				char aRx=MatrixKey();
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
						if(is_first){
							memset(str, 0, sizeof(str));
						memset(res, 0, sizeof(res));
							is_first=false;
					  }
						str[i++]=aRx;
			}else if(aRx=='='){
				  char* t;
	       double x = strtod(str,&t);
				 double ans=exp(x);
					sprintf(res,"%.2lf",ans);
					is_first=true;
				i=0;
			}else if(aRx=='c'){
					i=0;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
			
			is_first=true;
			}
			
			
			
			if(key0==0){
					HAL_Delay(5);
					idx=2;
					//ef_x_trg=0;
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				while(key0==0);
			}
				
}

void show_sub9_menu(u8g2_t *u8g2){
	key_scan_ud();
	
	static int i=0;
				u8g2_DrawStr(u8g2,50,50,res);
				u8g2_DrawStr(u8g2,1,d_y,"->");
	      u8g2_DrawStr(u8g2,14,20,"x:");
				u8g2_DrawStr(u8g2,14,30,"a:");
				u8g2_DrawStr(u8g2,25,20,str);
				u8g2_DrawStr(u8g2,25,30,av);
	      u8g2_DrawStr(u8g2,1,10,"a^x");
				gui_run(&d_y,&d_y_trg);
	

				char aRx=MatrixKey();
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
						if(is_first){
							memset(str, 0, sizeof(str));
						memset(res, 0, sizeof(res));
							memset(av, 0, sizeof(res));
							is_first=false;
					  }
						if(d_y==20) str[i++]=aRx;
						if(d_y==30) av[a_idx++]=aRx;
			}else if(aRx=='='){
				  char* t;
	       double x = strtod(str,&t);
				double a = strtod(av,&t);
				 double ans=pow(a,x);
					sprintf(res,"%.2lf",ans);
					is_first=true;
				i=0;
			}else if(aRx=='c'){
					i=0;
				a_idx=0;
				d_y_trg=20;
			memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				memset(av, 0, sizeof(res));
			
			is_first=true;
			}
			
			
			
			if(key0==0){
					HAL_Delay(5);
					idx=2;
				d_y_trg=20;
					//ef_x_trg=0;
				memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				memset(av, 0, sizeof(res));
				while(key0==0);
			}
				
}



void show_func_solu(u8g2_t* u8g2){
		u8g2_DrawStr(u8g2,1,10,"f(x)=0");
	u8g2_DrawStr(u8g2,1,20,"f(x)=");
	  u8g2_DrawStr(u8g2,31,20,str);
	u8g2_DrawStr(u8g2,50,50,res);
		/*
		if(!key_state){
				char aRx = MatrixKey();
				//strcat(str,(char*)c);
				
			if(aRx!='=' && aRx!='c'&&aRx!=' '){
					str[i++]=aRx;
			}
		}else if(key_state){
				char* s = MatrixKey_s();
				//strcat(str,s);
			if(s!=" "&&s!=""){
					strcat(str,s);
			}
		}
	*/
	
	char aRx = MatrixKey();
	
	if(aRx!='=' && aRx!='c'&&aRx!=' '){
			if(is_first){
					memset(str, 0, sizeof(str));
				memset(res, 0, sizeof(res));
				//memset(next, 0, sizeof(res));
				//emset(third, 0, sizeof(res));
					is_first=false;
			}
		}
	
		if(aRx=='='){
					HAL_Delay(5);
				double ans=solve(str);
				sprintf(res,"%.4lf",ans);
				is_first=true;
         HAL_Delay(5);
			}
		if(aRx=='c'){
			    HAL_Delay(5);
					memset(str, 0, sizeof(str));
				  memset(res, 0, sizeof(res));
					HAL_Delay(5);
			}
				//strcat(str,s);
			switch(aRx){
				case '1':{
						if(key_state) strcat(str,"sin(");
					else strcat(str,"1");
					break;
				}
				case '2':{
						if(key_state) strcat(str,"cos(");
					else strcat(str,"2");
					break;
				}
				case '3':{
						if(key_state) strcat(str,"tan(");
					else strcat(str,"3");
					break;
				}
				case '+':{
						if(!key_state) strcat(str,"+");
					else strcat(str,"log");
					break;
				}
				case '4':{
						if(key_state) strcat(str,"arcsin(");
					else strcat(str,"4");
					break;
				}
				case '5':{
						if(key_state) strcat(str,"arccos(");
					else strcat(str,"5");
					break;
				}
				case '6':{
						if(key_state) strcat(str,"arctan(");
					else strcat(str,"6");
					break;
				}
				case'-':{
						if(!key_state) strcat(str,"-");
					else strcat(str,"ln(");
					break;
				}
				case'7':{
						if(!key_state) strcat(str,"7");
					else strcat(str,"(");
					break;
				}
				case'8':{
						if(!key_state) strcat(str,"8");
					else strcat(str,"^");
					break;
				}
				case'9':{
						if(!key_state) strcat(str,"9");
					break;
				}
				case'*':{
						if(!key_state) strcat(str,"*");
					else strcat(str,"e");
					break;
				}
				case'/':{
						if(!key_state) strcat(str,"/");
					else strcat(str,"pi");
					break;
				}
				case'0':{
						if(!key_state) strcat(str,"0");
					else strcat(str,"x");
					break;
				}
			}
			
			
		
		
		
		if(key1==0){
			HAL_Delay(5);
				key_state=!key_state;
			while(key1==0);
		}else if(key0==0){
				HAL_Delay(5);
			idx=3;
			while(key0==0);
		}else if(key2==0){
				HAL_Delay(5);
			strcat(str,")");
			while(key2==0);
		}else if(wkup==1){
			HAL_Delay(5);
				strcat(str,"(");
			while(wkup==1);
		}
}
//int def_select=0;
int def_y=20,def_y_trg=20;
void show_def_solu(u8g2_t* u8g2){
	key_scan_ud();
		u8g2_DrawStr(u8g2,1,10,"f(x)|a->b");
	u8g2_DrawStr(u8g2,14,20,"a:");
	u8g2_DrawStr(u8g2,14,35,"b:");
	u8g2_DrawStr(u8g2,14,50,"f(x)=");
	u8g2_DrawStr(u8g2,1,def_y,"->");
	def_y_trg=15*(def_select+1)+5;
	u8g2_DrawStr(u8g2,25,20,av);
	u8g2_DrawStr(u8g2,25,35,bv);
	u8g2_DrawStr(u8g2,45,50,cv);
	u8g2_DrawStr(u8g2,50,60,res);
	gui_run(&def_y,&def_y_trg);
	char aRx=MatrixKey();
	
	
	
	if(aRx!='=' && aRx!='c'&&aRx!=' '){
			if(is_first){
					memset(str, 0, sizeof(str));
				memset(av, 0, sizeof(res));
				memset(bv, 0, sizeof(res));
				memset(cv, 0, sizeof(res));
				memset(res,0,sizeof(str));
					is_first=false;
				legal=true;
			}
		}
	switch(aRx){
				case '1':{
						if(key_state) strcat(str,"sin(");
					else strcat(str,"1");
					break;
				}
				case '2':{
						if(key_state) strcat(str,"cos(");
					else strcat(str,"2");
					break;
				}
				case '3':{
						if(key_state) strcat(str,"tan(");
					else strcat(str,"3");
					break;
				}
				case '+':{
						if(!key_state) strcat(str,"+");
					else strcat(str,"log");
					break;
				}
				case '4':{
						if(key_state) strcat(str,"arcsin(");
					else strcat(str,"4");
					break;
				}
				case '5':{
						if(key_state) strcat(str,"arccos(");
					else strcat(str,"5");
					break;
				}
				case '6':{
						if(key_state) strcat(str,"arctan(");
					else strcat(str,"6");
					break;
				}
				case'-':{
						if(!key_state) strcat(str,"-");
					else strcat(str,"ln(");
					break;
				}
				case'7':{
						if(!key_state) strcat(str,"7");
						else strcat(str,"(");
					break;
				}
				case'8':{
						if(!key_state) strcat(str,"8");
					else strcat(str,"^");
					break;
				}
				case'9':{
						if(!key_state) strcat(str,"9");
						else strcat(str,")");
					break;
				}
				case'*':{
						if(!key_state) strcat(str,"*");
					else strcat(str,"e");
					break;
				}
				case'/':{
						if(!key_state) strcat(str,"/");
					else strcat(str,"pi");
					break;
				}
				case'0':{
						if(!key_state) strcat(str,"0");
					else strcat(str,"x");
					break;
				}
				
			}
	
			if(def_select==0){
					strcat(av,str);
				memset(str,0,sizeof(str));
			}else if(def_select==1){
					strcat(bv,str);
					memset(str,0,sizeof(str));
			}else if(def_select==2){
					strcat(cv,str);
					memset(str,0,sizeof(str));
			}
	
			if(aRx=='c'){
					memset(str,0,sizeof(str));
					memset(av,0,sizeof(str));
					memset(bv,0,sizeof(str));
					memset(cv,0,sizeof(str));
				memset(res,0,sizeof(str));
				def_select=0;
			}else if(aRx=='='){
				char* end;
				double a=calc(av);
				double b = calc(bv);
					double ans=calc_def(cv,a,b);
				memset(res,0,sizeof(res));
				
				sprintf(res,"%.4lf",ans);
				
				is_first=true;
			}
			
			
			
			if(key2==0){
					HAL_Delay(5);
				menu_y_trg=20;
				idx=0;
				def_select=0;
				memset(str, 0, sizeof(str));
				memset(av, 0, sizeof(res));
				memset(bv, 0, sizeof(res));
				memset(cv, 0, sizeof(res));
				memset(res,0,sizeof(str));
				while(key2==0);
			}else if(key0==0){
					HAL_Delay(5);
				key_state=!key_state;
				while(key0==0);
			}
}










/********************************* end_of_file **********************************/


