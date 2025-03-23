#include "Locker.h"


/**
	* 函    数：密码键盘功能
	* 参    数：无
	* 返 回 值：无
	*/
void MatrixKey_Function(void)
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
				Unlock();		// 启用开锁进程
			}								
			else
			{
				// 未开锁
				OLED_Clear();
				OLED_ShowString(2, 20, "Unlock Failed!", OLED_8X16);
				OLED_Update();
				Delay_s(2);
				OLED_Clear(); OLED_Update();
			}
		}
	}
}


/**
	* 函    数：开锁程序
	* 参    数：无
	* 返 回 值：无
	* 注意事项：开锁5秒后自动回锁
	*/
void Unlock(void)
{
	// 补充开锁功能
}
