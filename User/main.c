#include "main.h"
#include "Locker.h"

void MatrixKey_Function(void);
void Fingerprint_Function(void);
void KeyBoard_Test(void);


SysPara AS608Para;			// 指纹模块AS608参数
uint16_t ValidN;			// 模块内有效指纹个数
int FP_Error;
u8 ensure;

uint8_t Press_Key = 0;
int Delate_ID = 0;
int Get_Data = 0;

uint8_t Display_State = 0;

void GUI_Display(void)
{
	OLED_ShowString(15, 0, "MrWei95's Locker", OLED_6X8);
	OLED_ShowString(0, 8, "-----------------------", OLED_6X8);
	if (Display_State == 0)
	{
		OLED_ShowChinese(15, 20, "使用指纹解锁");
		OLED_ShowChinese(0, 40, "按");
		OLED_ShowString(20, 40, "D", OLED_8X16);
		OLED_ShowChinese(30, 40, "使用密码解锁");
		OLED_Update();
	}
	else if (Display_State == 1)
	{
		// 未开锁
		OLED_Clear();
		OLED_ShowString(2, 20, "Unlock Failed!", OLED_8X16);
		OLED_Update();
		Delay_s(2);
		OLED_Clear(); OLED_Update();
	}
	
}


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// 设置系统中断优先级分组2
	
	OLED_Init();
	OLED_ShowString(0, 0, "Setting up...", OLED_6X8);
	OLED_Update();
	
	Locker_Init();
	MatrixKey_Init();
	USART2_Init();

	PS_StaGPIO_Init();					// 初始化FR读状态引脚
	Delay_ms(200);						// 延时200ms等待上电完成
	
	while (PS_HandShake(&AS608Addr))	// 与AS608模块握手，如果连不上会卡死在while中
	{
		OLED_ShowString(0, 8, "Connectting...", OLED_6X8);
		OLED_Update();
	}
	OLED_ShowString(0, 16, "Connect Success!", OLED_6X8);
	OLED_Update();
	Delay_s(2);
	OLED_Clear();
	GUI_Display();
	
	while (1)
	{
		//KeyBoard_Test();
		
		MatrixKey_Function();
		Fingerprint_Function();
	}
}


/**
	* 函    数：密码键盘功能
	* 参    数：无
	* 返 回 值：无
	*/
void MatrixKey_Function(void)
{
	char KeyValue = MatrixKey_GetValue();
	
	if (KeyValue)
	{
//		if ()
//		{
//			
//		}
	}
}


/**
	* 函    数：指纹解锁功能
	* 参    数：无
	* 返 回 值：无
	* 注意事项：开锁5秒后自动回锁
	*/
void Fingerprint_Function(void)
{
	// 指纹解锁
	if(PS_Sta)			// 检测PS_Sta状态，如果有手指按下
	{
		while(PS_Sta)
		{
			FP_Error = press_FR();	// 刷指纹
			if(FP_Error == 0)
			{
				//Display_State = 
				Unlock();			// 启用开锁进程
			}								
			else
			{
				Display_State = 1;	// 指纹解锁失败
			}
		}
	}
}


/**
	* 函    数：按键映射测试
	* 参    数：无
	* 返 回 值：当前按键返回值
	* 注意事项：按键映射可能混乱，需自行调整
	*/
void KeyBoard_Test(void)
{
	char KeyValue = 0;
	
	KeyValue = MatrixKey_GetValue();
	if (KeyValue)
	{
		OLED_Clear();
		OLED_ShowChar(1, 1, KeyValue, OLED_8X16);
		OLED_Update();
	}
}
