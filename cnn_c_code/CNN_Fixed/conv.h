#pragma once
#ifndef CONV_H_
#define CONV_H_


// INCLUDES
#include<stdint.h>
#include "orca_malloc.h"
#include "orca_printf.h"
#include "datachunk.h"

// DEFINITIONS
#define CVECTOR_LOGARITHMIC_GROWTH				(1)
#define Q										(15)
#define K										(1 << (Q - 1))
#define K1										(1 << (31 - 1))
#define MIN_SHORT								(-0x8000)
#define MAX_SHORT								(0x7FFF)
#define FIXED_POINT_FRACTIONAL_BITS				(15)

// TYPEDEF
typedef int16_t fixed_point_t;

// FUNCTION PROTOTYPES
int16_t sat16(int32_t x);
int16_t q_mul16(int16_t a, int16_t b);
int16_t q_add_sat(int16_t a, int16_t b);
int32_t q_add_sat32(int32_t a, int32_t b);
int32_t q_mul32(int16_t a, int16_t b);
int16_t convert32to16(int32_t temp);
//float fixed_to_float32(int32_t input);
//float fixed15_to_float(int16_t input);

#endif
