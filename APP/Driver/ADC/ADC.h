#ifndef __ADC_H
#define __ADC_H


#include "HeaderFiles.h"


void ADC_port_init(void); //adc端口初始化
void ADC_Init(void);     //  ADC 初始化

float drv_adc_read_ch0(void);      /* 电位器电压，单位 V */
float drv_adc_read_ch1(void);      /* DAC 回读电压，单位 V */
float drv_pt100_read_temp(void);   /* PT100 温度，单位 °C */
				    
#endif



