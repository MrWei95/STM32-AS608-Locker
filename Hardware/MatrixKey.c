#include "MatrixKey.h"


/**
	* 函    数：按键初始化
	* 参    数：无
	* 返 回 值：无
	*/
void MatrixKey_Init(void)
{
	RCC_APB2PeriphClockCmd(MATRIXKEY_RCC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;										// 推挽输出
	GPIO_InitStructure.GPIO_Pin = MATRIXKEY_1 | MATRIXKEY_2 | MATRIXKEY_3 | MATRIXKEY_4;	// 1 ~ 4
	GPIO_Init(MATRIXKEY_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;											// 引脚初始化为上拉输入
	GPIO_InitStructure.GPIO_Pin = MATRIXKEY_5 | MATRIXKEY_6 | MATRIXKEY_7 | MATRIXKEY_8;	// 5 ~ 8
	GPIO_Init(MATRIXKEY_PORT, &GPIO_InitStructure);
}

/**
	* 函    数：按键获取键码
	* 参    数：无
	* 返 回 值：按下按键的键码值
	* 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
	*/
char MatrixKey_GetValue(void)
{
	char KeyValue = 0;
	
	GPIO_Write(MATRIXKEY_PORT,((MATRIXKEY_PORT->ODR & 0xff00 )| 0x1803));
	if((MATRIXKEY_PORT->IDR & 0x00f0)==0x0000)
		return 0;
	else
	{
		Delay_ms(20);
		if((MATRIXKEY_PORT->IDR & 0x00f0)==0x0000)
		return 0;
	}
	
	GPIO_Write(MATRIXKEY_PORT,(MATRIXKEY_PORT->ODR & 0xe7fc )| 0x0001);			// ?PA8-11??0001,?????
	//printf("0x%x\r\n",KEY4_4PORT->IDR & 0x00f0);
	switch(MATRIXKEY_PORT->IDR & 0x00f0)
	{
		case 0x0010 : KeyValue='A';break;
		case 0x0020 : KeyValue='B';break;
		case 0x0040 : KeyValue='C';break;
		case 0x0080 : KeyValue='D';break;	
	} while((MATRIXKEY_PORT->IDR & 0x00f0)!=0x0000);

	GPIO_Write(MATRIXKEY_PORT,(MATRIXKEY_PORT->ODR & 0xe7fc) | 0x0002);			// ?PA8-11??0010,?????
	//printf("0x%x\r\n",KEY4_4PORT->IDR & 0x00f0);
	switch(MATRIXKEY_PORT->IDR & 0x00f0)
	{
		case 0x0010 : KeyValue='3';break;
		case 0x0020 : KeyValue='6';break;
		case 0x0040 : KeyValue='9';break;
		case 0x0080 : KeyValue='#';break;	
	} while((MATRIXKEY_PORT->IDR & 0x00f0)!=0x0000);

	GPIO_Write(MATRIXKEY_PORT,(MATRIXKEY_PORT->ODR & 0xe7fc )| 0x0800);			// ?PA8-11??0100,?????
	//printf("0x%x\r\n",KEY4_4PORT->IDR & 0x00f0);
	switch(MATRIXKEY_PORT->IDR & 0x00f0)
	{
		case 0x0010 : KeyValue='2';break;
		case 0x0020 : KeyValue='5';break;
		case 0x0040 : KeyValue='8';break;
		case 0x0080 : KeyValue='0';break;	
	} while((MATRIXKEY_PORT->IDR & 0x00f0)!=0x0000);

	GPIO_Write(MATRIXKEY_PORT,(MATRIXKEY_PORT->ODR & 0xe7fc )| 0x1000);			// ?PA8-11??1000,?????
	//printf("0x%x\r\n",KEY4_4PORT->IDR & 0x00f0);
	switch(MATRIXKEY_PORT->IDR & 0x00f0)
	{
		case 0x0010 : KeyValue='1';break;
		case 0x0020 : KeyValue='4';break;
		case 0x0040 : KeyValue='7';break;
		case 0x0080 : KeyValue='*';break;	
	} while((MATRIXKEY_PORT->IDR & 0x00f0)!=0x0000);
	
	return KeyValue;
}
