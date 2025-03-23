#include "main.h"
#include "Locker.h"


void KeyBoard_Test(void);


SysPara AS608Para;			// 指纹模块AS608参数
uint16_t ValidN;			// 模块内有效指纹个数
int FP_Error;
u8 ensure;

uint8_t Press_Key = 0;
int Delate_ID = 0;
int Get_Data = 0;

void GUI_Display(void)
{
	OLED_ShowString(15, 0, "MrWei95's Locker", OLED_6X8);
	OLED_Update();
		
	MatrixKey_Function();
	Fingerprint_Function();
}


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// 设置系统中断优先级分组2
	
	OLED_Init();
	OLED_ShowString(0, 0, "Setting up...", OLED_8X16);
	OLED_Update();
	
	MatrixKey_Init();
	USART2_Init();

	PS_StaGPIO_Init();					// 初始化FR读状态引脚
	Delay_ms(150);						// 延时150ms等待上电完成
	
	while (PS_HandShake(&AS608Addr))	// 与AS608模块握手，如果连不上会卡死在while中
	{
		OLED_ShowString(0, 18, "Connectting...", OLED_8X16);
		OLED_Update();
	}
	OLED_ShowString(0, 36, "Connect Success!", OLED_8X16);
	OLED_Update();
	Delay_s(2);
	OLED_Clear(); OLED_Update();
	
	while (1)
	{
		//KeyBoard_Test();
		
		GUI_Display();
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
