#ifndef __MATRIXKEY_H
#define __MATRIXKEY_H

/**
	* 	键盘布局（标准4×4）
	*     列1  列2  列3  列4
	*   +----+----+----+----+
	* 行1 | 1  | 2  | 3  | A  |
	* 行2 | 4  | 5  | 6  | B  |
	* 行3 | 7  | 8  | 9  | C  |
	* 行4 | *  | 0  | #  | D  |
	*   +----+----+----+----+
	*/

#include "main.h"

#define		MATRIXKEY_RCC		RCC_APB2Periph_GPIOA
#define		MATRIXKEY_PORT		GPIOA

#define		MATRIXKEY_1			GPIO_Pin_12
#define		MATRIXKEY_2			GPIO_Pin_11
#define		MATRIXKEY_3			GPIO_Pin_1
#define		MATRIXKEY_4			GPIO_Pin_0

#define		MATRIXKEY_5			GPIO_Pin_4
#define		MATRIXKEY_6			GPIO_Pin_5
#define		MATRIXKEY_7			GPIO_Pin_6
#define		MATRIXKEY_8			GPIO_Pin_7

void MatrixKey_Init(void);
char MatrixKey_GetValue(void);

#endif
