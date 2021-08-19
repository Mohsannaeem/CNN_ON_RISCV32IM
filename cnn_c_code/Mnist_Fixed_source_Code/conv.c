#include "conv.h" 

// saturate to range of int16_t
int16_t sat16(int32_t x)
{
	if (x > MAX_SHORT)
		return MAX_SHORT;
	else if (x < MIN_SHORT)
		return MIN_SHORT;
	else
		return (int16_t)x;
}

int16_t q_mul16(int16_t a, int16_t b)
{
	int32_t temp;
	temp = (int32_t)a * (int32_t)b;				// result type is operand's type
	return (temp >> Q);
}

int32_t q_mul32(int16_t a, int16_t b)
{
	int32_t temp;
	temp = (int32_t)a * (int32_t)b;
	float c = (a) / (float)(1 << 15); //Fixed to Float of 1.15
	float v = b / (float)(1 << 15); //Fixed to Float of 1.15
	float value = temp / (float)(1 << 30); //Fixed to Float of 2.30
	//printf("%f	%f	%f\n", v, c, value);
	return temp;
}


int16_t q_add_sat(int16_t a, int16_t b)
{
	int16_t result;
	int32_t tmp;

	tmp = (int32_t)a + (int32_t)b;
	if (tmp > 0x7FFF)
		tmp = 0x7FFF;
	if (tmp < -1 * 0x8000)
		tmp = -1 * 0x8000;
	result = (int16_t)tmp;

	return result;
}
int32_t q_add_sat32(int32_t a, int32_t b)
{
	int32_t result;
	int64_t tmp;

	tmp = (int64_t)a + (int64_t)b;
	if (tmp > 2147483647)
		tmp = 2147483647;
	if (tmp < -2147483647-1)
		tmp = -2147483647-1;
	result = (int32_t)tmp;

	return result;
}

int16_t convert32to16(int32_t temp)
{
	return sat16((temp >> Q));
}

float fixed_to_float32(int32_t input)
{
	return ((float)input / (float)(1 << 30));
}

int32_t float_to_fixed32(double input)
{
	return (int32_t)((input * (1 << 31)));
}

float fixed15_to_float(int16_t input)
{
	float temp = input;
	temp = temp / (float)(1 << FIXED_POINT_FRACTIONAL_BITS);
	return temp;
}
