/**
 * @file user_main.c
 * @author TITH (1023515576@qq.com)
 * @brief
 * @version 0.1
 * @date 2022-07-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "user_main.h"
#include "main.h"
#include <stdbool.h>
#include "wtr_mavlink.h"
#include "adc.h"
#include "usart.h"

int i = 0;
int left_x;
int left_y;
int right_x;
int right_y;

mavlink_controller_t TxData;

void user_main(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

	WTR_MAVLink_Init(&huart1, MAVLINK_COMM_0);

	uint8_t Button[8] = {0};

	while (true)
	{

		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_SET)
		{
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_SET)
			{
				Button[0] = 1;
			}
		}
		else
		{
			Button[0] = 0;
		}

		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == GPIO_PIN_SET)
		{
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == GPIO_PIN_SET)
			{
				Button[1] = 1;
			}
		}
		else
		{
			Button[1] = 0;
		}

		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_SET)
		{
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_SET)
			{
				Button[2] = 1;
			}
		}
		else
		{
			Button[2] = 0;
		}

		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_SET)
		{
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_SET)
			{
				Button[3] = 1;
			}
		}
		else
		{
			Button[3] = 0;
		}

		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET)
		{
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET)
			{
				Button[4] = 1;
			}
		}
		else
		{
			Button[4] = 0;
		}

		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET)
		{
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET)
			{
				Button[5] = 1;
			}
		}
		else
		{
			Button[5] = 0;
		}

		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_SET)
		{
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_SET)
			{
				Button[6] = 1;
			}
		}
		else
		{
			Button[6] = 0;
		}

		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET)
		{
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET)
			{
				Button[7] = 1;
			}
		}
		else
		{
			Button[7] = 0;
		}

		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 10);
		left_y = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 10);
		left_x = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 10);
		right_y = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 10);
		right_x = HAL_ADC_GetValue(&hadc1);

		TxData.left_x = -left_x + 2048 - 155;
		TxData.left_y = -left_y + 2048 + 27;
		TxData.right_x = -right_x + 2048 - 100;
		TxData.right_y = -right_y + 2048 + 68;

		TxData.buttons = 0;

		for (int i = 0; i < 8; i++)
		{
			TxData.buttons |= Button[i] << i;
		}

		mavlink_msg_controller_send_struct(MAVLINK_COMM_0, &TxData);

		HAL_Delay(10);
	}
}
