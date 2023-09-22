#ifndef MQ2_H
#define MQ2_H
#include "stdint.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "freertos/task.h"
#include "freertos/FreeRTOS.h"

#define   NO__SAMPLE   64
#define   Vref    3.3
#define   V0      0.8              //gia tri sensor volt khi o khi binh thuong
#define   RS_Air  31               //gia tri RS_AIR dien tro khi o khi binh thuong
#define   R0      7                //gia tri dien tro R0 = RS_AIR/4.4

typedef struct {
	 float MQ_Slope;       //gia tri do doc
	 float MQ_Block_Point; //gia tri diem chan
	 float MQ_RS_gas;      //gia tri RS khi co khi khac
	 float MQ_Ratio;       //Ti so RS/R0
	 float MQ_Sensor_Volt; //Dien ap do duoc tai chan ADC
}TypeDef_MQ ;

void  MQ_Init(ADC_HandleTypeDef *_hadc,TypeDef_MQ *MQ , float _MQ_Slope , float _MQ_Block_Point);
void  MQ_Read_Sensor(TypeDef_MQ *MQ);
float MQ_adcToVolt(uint16_t adc_value);
void  MQ_set_Ratio(TypeDef_MQ *MQ);
void  MQ_set_Sensor_Volt(TypeDef_MQ *MQ , uint16_t value_adc);
void  MQ_set_RS_Gas(TypeDef_MQ *MQ);


#endif
