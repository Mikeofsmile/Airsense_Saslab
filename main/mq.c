#include "../Library/mq.h"
#include "math.h"

__weak void MQ_CallBack_Data(float ppm)
{
}

float MQ_adcToVolt(uint16_t adc_value)
{
	return adc_value * 3.3 / 4095;
}
void MQ_Init(TypeDef_MQ *MQ, float _MQ_Slope, float _MQ_Block_Point)
{
	MQ->MQ_Slope = _MQ_Slope;
	MQ->MQ_Block_Point = _MQ_Block_Point;
}
void MQ_set_RS_Gas(TypeDef_MQ *MQ)
{
	MQ->MQ_RS_gas = 3.3 * 10 / (MQ->MQ_Sensor_Volt - 0.1) - 10;
}
void MQ_set_Sensor_Volt(TypeDef_MQ *MQ, uint16_t value_adc)
{
	MQ->MQ_Sensor_Volt = MQ_adcToVolt(value_adc);
}
void MQ_set_Ratio(TypeDef_MQ *MQ)
{
	MQ->MQ_Ratio = MQ->MQ_RS_gas / R0;
}
void MQ_Read_Sensor(TypeDef_MQ *MQ, unit32_t adc_value)
{
    uint32_t val_type= adc_value;
	MQ_set_Sensor_Volt(MQ, val_type);
	MQ_set_RS_Gas(MQ);
	MQ_set_Ratio(MQ);
	float ppm_log = (log10(MQ->MQ_Ratio) - MQ->MQ_Block_Point) / MQ->MQ_Slope;
	float ppm = pow(10, ppm_log);
	MQ_CallBack_Data(ppm);
	HAL_ADC_Stop(hadc);
}
