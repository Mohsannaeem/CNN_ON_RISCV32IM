#pragma once
#ifndef __NEW_VARIABLE_H__
#define __NEW_VARIABLE_H__
#include "stdint.h"
extern int flag;
extern int16_t tmp_single_depth11n[28][28];
extern int conv_length[];
extern int conv_depth[];
extern int conv_row[];
extern int conv_col[];
extern char conv_border[];
extern int16_t conv_bias1n[32];//change
extern int16_t conv_bias2n[64];
extern const int layer_count;
extern char activation_activator[];
extern int16_t tmp_depths1n[32][1][3][3];
extern int16_t  tmp_depths2n[64][32][3][3];
extern int16_t dense_weight1n[12544][128];
extern int16_t dense_weight2n[128][10];
extern int16_t dense_bias1n[128];
extern int16_t  dense_bias2n[];
extern int activation_counter;
extern int conv_counter;
extern int dense_counter;

#endif