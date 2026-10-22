
#ifndef __USART_H__
#define __USART_H__

/************************* 头文件 *************************/
#include "HeaderFiles.h"

/************************* 宏定义 *************************/
#define USART_PORT GPIOA
#define USART USART1
#define USART_TX_Pin GPIO_PIN_2
#define USART_RX_Pin GPIO_PIN_3
#define USARTX_RCU RCU_USART1
#define USART_PIN_RCU RCU_GPIOA


#define USART_485_CS_RCU RCU_GPIOA
#define USART_485_CS_PORT GPIOA
#define USARTX_485_CS_Pin GPIO_PIN_1

#define USARTX_485_Send 1
#define USARTX_485_Receive 0



/************************ 变量定义 ************************/


/************************ 函数定义 ************************/

void usart_init(void);
void usart_send_str(uint8_t* str, uint8_t len);
void usart_recv_buf(void);
void RS485_SendData(uint8_t* str,size_t data_len);

#endif // !__USART_H__
/****************************End*****************************/
